#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/LevelTools.hpp>
#include <Geode/modify/LocalLevelManager.hpp>

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

using namespace geode::prelude;

namespace GeoBRMainLevels {
    struct Entry {
        int slot = 0;
        int serverID = 0;
        std::string name;
        std::string levelString;
    };

    inline std::vector<Entry>& entries() {
        static std::vector<Entry> value;
        return value;
    }

    inline bool loaded = false;
    inline bool enabled = true;

    // The first implementation intentionally uses a local manifest/cache.
    // This gives us a deterministic Main Levels hook before we connect the
    // manifest to the GeoBR GDPS API.
    inline void loadManifest() {
        if (loaded) return;
        loaded = true;

        auto dir = Mod::get()->getSaveDir();
        auto manifest = dir / "main_levels.json";

        if (!std::filesystem::exists(manifest)) {
            auto sample = R"({
  "enabled": true,
  "levels": []
})";
            file::createDirectoryAll(dir).err();
            file::writeString(manifest, sample).err();
            log::info("GeoBR Main Levels: created manifest at {}", manifest.string());
            return;
        }

        auto raw = file::readString(manifest);
        if (raw.isErr()) {
            log::error("GeoBR Main Levels: could not read manifest: {}", raw.unwrapErr());
            return;
        }

        auto json = matjson::parse(raw.unwrap());
        if (json.isErr()) {
            log::error("GeoBR Main Levels: invalid manifest: {}", json.unwrapErr());
            return;
        }

        auto root = json.unwrap();
        if (root.contains("enabled")) {
            enabled = root["enabled"].asBool().unwrapOr(true);
        }

        if (!root.contains("levels") || !root["levels"].isArray()) return;

        for (auto const& item : root["levels"]) {
            Entry entry;
            entry.slot = item["slot"].asInt().unwrapOr(0);
            entry.serverID = item["server_id"].asInt().unwrapOr(0);
            entry.name = item["name"].asString().unwrapOr("");
            entry.levelString = item["level_string"].asString().unwrapOr("");

            if (entry.slot > 0 && (!entry.levelString.empty() || entry.serverID > 0)) {
                entries().push_back(std::move(entry));
            }
        }

        std::sort(entries().begin(), entries().end(), [](auto const& a, auto const& b) {
            return a.slot < b.slot;
        });

        log::info("GeoBR Main Levels: loaded {} configured slots", entries().size());
    }

    inline Entry const* find(int slot) {
        loadManifest();
        auto it = std::find_if(entries().begin(), entries().end(), [slot](auto const& e) {
            return e.slot == slot;
        });
        return it == entries().end() ? nullptr : &*it;
    }

    inline std::string getLevelString(int slot) {
        auto entry = find(slot);
        if (!entry || entry->levelString.empty()) return {};
        return entry->levelString;
    }
}

// Main Levels are constructed through LevelSelectLayer. This is our first
// reliable entry point: we let Geometry Dash build the normal page, then keep
// the GeoBR routing decision isolated here.
class $modify(GeoBRLevelSelectLayer, LevelSelectLayer) {
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) return false;

        GeoBRMainLevels::loadManifest();
        if (!GeoBRMainLevels::enabled) return true;

        log::info("GeoBR Main Levels: page {} detected", page);
        return true;
    }
};

// Geometry Dash asks LevelTools for the metadata of a Main Level. By mapping
// the vanilla slot to GeoBR's configured server ID, the rest of the game can
// continue using the normal Main Level UI and play flow.
class $modify(GeoBRLevelTools, LevelTools) {
    static GJGameLevel* getLevel(int levelID, bool dontGetLevelString) {
        auto original = LevelTools::getLevel(levelID, dontGetLevelString);

        if (!GeoBRMainLevels::enabled) return original;

        auto entry = GeoBRMainLevels::find(levelID);
        if (!entry || !original) return original;

        original->m_levelID = entry->serverID > 0 ? entry->serverID : levelID;
        if (!entry->name.empty()) original->m_levelName = entry->name;

        log::debug(
            "GeoBR Main Levels: slot {} -> server level {} ({})",
            levelID,
            original->m_levelID,
            original->m_levelName
        );

        return original;
    }
};

// Main level geometry is stored separately from the normal local Main Level
// files. When a GeoBR slot has a cached level string, Geometry Dash receives
// that string through the exact function used for Main Level data.
class $modify(GeoBRLocalLevelManager, LocalLevelManager) {
    gd::string getMainLevelString(int levelID) {
        if (GeoBRMainLevels::enabled) {
            auto custom = GeoBRMainLevels::getLevelString(levelID);
            if (!custom.empty()) {
                log::debug("GeoBR Main Levels: serving custom string for slot {}", levelID);
                return custom.c_str();
            }
        }

        return LocalLevelManager::getMainLevelString(levelID);
    }
};

$execute {
    GeoBRMainLevels::loadManifest();
    log::info("GeoBR Main Levels: system initialized");
};
