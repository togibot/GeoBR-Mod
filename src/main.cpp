#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class GeoBRNewsPopup : public CCLayerColor {
public:
    static GeoBRNewsPopup* create() {
        auto layer = new GeoBRNewsPopup();
        if (layer && layer->init()) {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
        return nullptr;
    }

    bool init() {
        if (!CCLayerColor::initWithColor({0, 0, 0, 150})) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        setContentSize(winSize);
        setKeypadEnabled(true);
        setTouchEnabled(true);

        auto bg = CCScale9Sprite::create("GJ_square01.png", {0, 0, 80, 80});
        bg->setContentSize({430, 270});
        bg->setPosition({winSize.width / 2, winSize.height / 2});
        addChild(bg);

        auto title = CCLabelBMFont::create("GEOBR NEWS", "goldFont.fnt");
        title->setPosition({winSize.width / 2, winSize.height / 2 + 105});
        title->setScale(0.8f);
        addChild(title);

        auto latest = CCLabelBMFont::create(
            "LATEST\n\n"
            "• GeoBR Mod is now available!\n"
            "• Creator Battles are back!\n"
            "• New GeoBR events are coming soon!\n\n"
            "Stay tuned for more updates.",
            "chatFont.fnt"
        );
        latest->setAlignment(kCCTextAlignmentCenter);
        latest->setPosition({winSize.width / 2, winSize.height / 2 + 5});
        latest->setScale(0.72f);
        addChild(latest);

        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSprite->setScale(0.8f);
        auto closeButton = CCMenuItemSpriteExtra::create(
            closeSprite,
            this,
            menu_selector(GeoBRNewsPopup::onClose)
        );

        auto menu = CCMenu::create();
        menu->setPosition({winSize.width / 2, winSize.height / 2 - 105});
        menu->addChild(closeButton);
        addChild(menu);

        return true;
    }

    void onClose(CCObject*) {
        removeFromParentAndCleanup(true);
    }

    void keyBackClicked() override {
        removeFromParentAndCleanup(true);
    }
};

class GeoBRHubPopup : public CCLayerColor {
public:
    static GeoBRHubPopup* create() {
        auto layer = new GeoBRHubPopup();
        if (layer && layer->init()) {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
        return nullptr;
    }

    bool init() {
        if (!CCLayerColor::initWithColor({0, 0, 0, 150})) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        setContentSize(winSize);
        setKeypadEnabled(true);
        setTouchEnabled(true);

        auto bg = CCScale9Sprite::create("GJ_square01.png", {0, 0, 80, 80});
        bg->setContentSize({430, 250});
        bg->setPosition({winSize.width / 2, winSize.height / 2});
        addChild(bg);

        auto title = CCLabelBMFont::create("GEOBR HUB", "goldFont.fnt");
        title->setPosition({winSize.width / 2, winSize.height / 2 + 90});
        title->setScale(0.85f);
        addChild(title);

        auto subtitle = CCLabelBMFont::create(
            "COMMUNITY HUB",
            "chatFont.fnt"
        );
        subtitle->setPosition({winSize.width / 2, winSize.height / 2 + 62});
        subtitle->setScale(0.7f);
        addChild(subtitle);

        auto newsSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        newsSprite->setScale(0.85f);
        auto newsButton = CCMenuItemSpriteExtra::create(
            newsSprite,
            this,
            menu_selector(GeoBRHubPopup::onNews)
        );

        auto newsMenu = CCMenu::create();
        newsMenu->setPosition({winSize.width / 2, winSize.height / 2 + 5});
        newsMenu->addChild(newsButton);
        addChild(newsMenu);

        auto newsLabel = CCLabelBMFont::create("NEWS", "bigFont.fnt");
        newsLabel->setPosition({winSize.width / 2, winSize.height / 2 - 38});
        newsLabel->setScale(0.55f);
        addChild(newsLabel);

        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSprite->setScale(0.8f);
        auto closeButton = CCMenuItemSpriteExtra::create(
            closeSprite,
            this,
            menu_selector(GeoBRHubPopup::onClose)
        );

        auto closeMenu = CCMenu::create();
        closeMenu->setPosition({winSize.width / 2, winSize.height / 2 - 90});
        closeMenu->addChild(closeButton);
        addChild(closeMenu);

        return true;
    }

    void onNews(CCObject*) {
        auto popup = GeoBRNewsPopup::create();
        if (popup) {
            getParent()->addChild(popup, 1000);
            removeFromParentAndCleanup(true);
        }
    }

    void onClose(CCObject*) {
        removeFromParentAndCleanup(true);
    }

    void keyBackClicked() override {
        removeFromParentAndCleanup(true);
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
        auto popup = GeoBRHubPopup::create();
        if (popup) {
            this->getParent()->addChild(popup, 1000);
        }
    }
};
