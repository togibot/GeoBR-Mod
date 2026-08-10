#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(GeoBRMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("GeoBR: bottom-menu was not found");
            return true;
        }

        auto icon = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        if (!icon) {
            log::warn("GeoBR: could not create button sprite");
            return true;
        }

        icon->setScale(0.8f);

        auto button = CCMenuItemSpriteExtra::create(
            icon,
            this,
            menu_selector(GeoBRMenuLayer::onGeoBR)
        );

        button->setID("hub-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        log::info("GeoBR: Hub button loaded");
        return true;
    }

    void onGeoBR(CCObject*) {
        FLAlertLayer::create(
            "GeoBR Hub",
            "COMMUNITY HUB\n\nProfile   |   Ranking   |   Events\nCreator Battles   |   Badges\n\nGeoBR Mod 1.0.0",
            "OK"
        )->show();
    }
};
