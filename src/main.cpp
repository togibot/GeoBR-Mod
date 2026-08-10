#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static constexpr float kPanelWidth = 430.f;
static constexpr float kPanelHeight = 270.f;

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
        if (!CCLayerColor::initWithColor({0, 0, 0, 175})) return false;

        auto win = CCDirector::sharedDirector()->getWinSize();
        setContentSize(win);
        setKeypadEnabled(true);
        setTouchEnabled(true);

        auto bg = CCScale9Sprite::create("GJ_square01.png", {0, 0, 80, 80});
        bg->setContentSize({kPanelWidth, kPanelHeight});
        bg->setPosition({win.width / 2, win.height / 2});
        addChild(bg);

        auto title = CCLabelBMFont::create("NOTÍCIAS GEOBR", "goldFont.fnt");
        title->setPosition({win.width / 2, win.height / 2 + 101});
        title->setScale(0.78f);
        addChild(title);

        auto line = CCScale9Sprite::create("GJ_square02.png");
        line->setContentSize({330, 2});
        line->setOpacity(80);
        line->setPosition({win.width / 2, win.height / 2 + 78});
        addChild(line);

        auto news = CCLabelBMFont::create(
            "• O mod GeoBR está disponível!\n"
            "• Creator Battles estão de volta!\n"
            "• Novos eventos GeoBR estão chegando!",
            "chatFont.fnt"
        );
        news->setAlignment(kCCTextAlignmentLeft);
        news->setPosition({win.width / 2 - 150, win.height / 2 + 15});
        news->setScale(0.70f);
        addChild(news);

        auto footer = CCLabelBMFont::create("Fique de olho nas próximas novidades.", "chatFont.fnt");
        footer->setPosition({win.width / 2, win.height / 2 - 58});
        footer->setScale(0.55f);
        footer->setOpacity(190);
        addChild(footer);

        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSprite->setScale(0.78f);
        auto close = CCMenuItemSpriteExtra::create(
            closeSprite, this, menu_selector(GeoBRNewsPopup::onClose)
        );

        auto menu = CCMenu::create();
        menu->setPosition({win.width / 2, win.height / 2 - 103});
        menu->addChild(close);
        addChild(menu);

        return true;
    }

    void onClose(CCObject*) { removeFromParentAndCleanup(true); }
    void keyBackClicked() override { removeFromParentAndCleanup(true); }
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
        if (!CCLayerColor::initWithColor({0, 0, 0, 170})) return false;

        auto win = CCDirector::sharedDirector()->getWinSize();
        setContentSize(win);
        setKeypadEnabled(true);
        setTouchEnabled(true);

        auto bg = CCScale9Sprite::create("GJ_square01.png", {0, 0, 80, 80});
        bg->setContentSize({460, 300});
        bg->setPosition({win.width / 2, win.height / 2});
        addChild(bg);

        auto title = CCLabelBMFont::create("GEOBR", "goldFont.fnt");
        title->setPosition({win.width / 2, win.height / 2 + 115});
        title->setScale(1.0f);
        addChild(title);

        auto subtitle = CCLabelBMFont::create("CENTRAL DA COMUNIDADE", "chatFont.fnt");
        subtitle->setPosition({win.width / 2, win.height / 2 + 88});
        subtitle->setScale(0.62f);
        subtitle->setOpacity(210);
        addChild(subtitle);

        // Linha divisória do cabeçalho.
        auto line = CCScale9Sprite::create("GJ_square02.png");
        line->setContentSize({350, 2});
        line->setOpacity(85);
        line->setPosition({win.width / 2, win.height / 2 + 68});
        addChild(line);

        // Cartão de notícias: o botão usa o mesmo tamanho visual dos botões normais do GD.
        auto newsSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        if (newsSprite) {
            newsSprite->setScale(1.0f);
            auto newsButton = CCMenuItemSpriteExtra::create(
                newsSprite, this, menu_selector(GeoBRHubPopup::onNews)
            );
            newsButton->setID("news-button"_spr);

            auto newsMenu = CCMenu::create();
            newsMenu->setPosition({win.width / 2 - 118, win.height / 2 + 18});
            newsMenu->addChild(newsButton);
            addChild(newsMenu);

            auto newsLabel = CCLabelBMFont::create("NOTÍCIAS", "bigFont.fnt");
            newsLabel->setPosition({win.width / 2 - 118, win.height / 2 - 35});
            newsLabel->setScale(0.52f);
            addChild(newsLabel);
        }

        // Botões de acesso rápido. Eles ficam visíveis no Update 1 e avisam quando a função ainda está em desenvolvimento.
        addComingSoonButton(win, "PERFIL", win.width / 2, win.height / 2 + 18);
        addComingSoonButton(win, "RANKING", win.width / 2 + 118, win.height / 2 + 18);

        auto hint = CCLabelBMFont::create("Mais recursos serão adicionados em breve", "chatFont.fnt");
        hint->setPosition({win.width / 2, win.height / 2 - 77});
        hint->setScale(0.52f);
        hint->setOpacity(175);
        addChild(hint);

        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        closeSprite->setScale(0.78f);
        auto close = CCMenuItemSpriteExtra::create(
            closeSprite, this, menu_selector(GeoBRHubPopup::onClose)
        );

        auto closeMenu = CCMenu::create();
        closeMenu->setPosition({win.width / 2, win.height / 2 - 113});
        closeMenu->addChild(close);
        addChild(closeMenu);

        return true;
    }

private:
    void addComingSoonButton(CCSize win, const char* label, float x, float y) {
        auto sprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        if (!sprite) return;
        sprite->setScale(1.0f);

        auto button = CCMenuItemSpriteExtra::create(
            sprite, this, menu_selector(GeoBRHubPopup::onComingSoon)
        );
        button->setUserData(const_cast<char*>(label));

        auto menu = CCMenu::create();
        menu->setPosition({x, y});
        menu->addChild(button);
        addChild(menu);

        auto text = CCLabelBMFont::create(label, "bigFont.fnt");
        text->setPosition({x, y - 53});
        text->setScale(0.49f);
        addChild(text);
    }

    void onNews(CCObject*) {
        auto popup = GeoBRNewsPopup::create();
        if (popup) {
            getParent()->addChild(popup, 1000);
            removeFromParentAndCleanup(true);
        }
    }

    void onComingSoon(CCObject*) {
        FLAlertLayer::create("GeoBR", "Esta função estará disponível em uma próxima atualização.", "OK")->show();
    }

    void onClose(CCObject*) { removeFromParentAndCleanup(true); }
    void keyBackClicked() override { removeFromParentAndCleanup(true); }
};

class $modify(GeoBRMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("GeoBR: bottom-menu não encontrado");
            return true;
        }

        auto icon = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        if (!icon) {
            log::warn("GeoBR: não foi possível criar o botão");
            return true;
        }

        // Mesmo tamanho visual dos botões do menu inferior.
        icon->setScale(1.0f);

        auto button = CCMenuItemSpriteExtra::create(
            icon, this, menu_selector(GeoBRMenuLayer::onGeoBR)
        );
        button->setID("geobr-hub-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        log::info("GeoBR: Hub carregado");
        return true;
    }

    void onGeoBR(CCObject*) {
        auto popup = GeoBRHubPopup::create();
        if (popup) this->getParent()->addChild(popup, 1000);
    }
};
