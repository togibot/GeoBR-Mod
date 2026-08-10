#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class GeoBRHub : public FLAlertLayer {
protected:
    bool init() {
        if (!FLAlertLayer::init(320.f, 220.f)) {
            return false;
        }

        this->setTitle("GeoBR Hub");

        auto title = CCLabelBMFont::create("COMMUNITY HUB", "goldFont.fnt");
        title->setScale(0.65f);
        title->setPosition({160.f, 175.f});
        m_mainLayer->addChild(title);

        auto info = CCLabelBMFont::create(
            "Profile   |   Ranking   |   Events\nCreator Battles   |   Badges",
            "bigFont.fnt"
        );
        info->setAlignment(kCCTextAlignmentCenter);
        info->setScale(0.42f);
        info->setPosition({160.f, 125.f});
        m_mainLayer->addChild(info);

        auto status = CCLabelBMFont::create("GeoBR Mod 1.0.0", "chatFont.fnt");
        status->setScale(0.65f);
        status->setPosition({160.f, 55.f});
        m_mainLayer->addChild(status);

        return true;
    }

public:
    static GeoBRHub* create() {
        auto ret = new GeoBRHub();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

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
        GeoBRHub::create()->show();
    }
};
