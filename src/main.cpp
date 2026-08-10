#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

static constexpr float kPanelWidth = 430.f;
static constexpr float kPanelHeight = 270.f;

class GeoBRNewsPopup : public CCLayerColor {
public:
    static GeoBRNewsPopup* create() {
        auto layer = new GeoBRNewsPopup();
        if (layer && layer->init()) { layer->autorelease(); return layer; }
        CC_SAFE_DELETE(layer); return nullptr;
    }
    bool init() {
        if (!CCLayerColor::initWithColor({0, 0, 0, 175})) return false;
        auto win = CCDirector::sharedDirector()->getWinSize();
        setContentSize(win); setKeypadEnabled(true); setTouchEnabled(true);
        auto bg = CCScale9Sprite::create("GJ_square01.png", {0,0,80,80});
        bg->setContentSize({kPanelWidth,kPanelHeight}); bg->setPosition({win.width/2,win.height/2}); addChild(bg);
        auto title = CCLabelBMFont::create("NOTÍCIAS GEOBR", "goldFont.fnt");
        title->setPosition({win.width/2,win.height/2+101}); title->setScale(.78f); addChild(title);
        auto news = CCLabelBMFont::create("• O mod GeoBR está disponível!\n• Creator Battles estão de volta!\n• Novos eventos GeoBR estão chegando!", "chatFont.fnt");
        news->setAlignment(kCCTextAlignmentLeft); news->setPosition({win.width/2-150,win.height/2+15}); news->setScale(.70f); addChild(news);
        auto footer = CCLabelBMFont::create("Fique de olho nas próximas novidades.", "chatFont.fnt");
        footer->setPosition({win.width/2,win.height/2-58}); footer->setScale(.55f); footer->setOpacity(190); addChild(footer);
        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"); closeSprite->setScale(.78f);
        auto close = CCMenuItemSpriteExtra::create(closeSprite,this,menu_selector(GeoBRNewsPopup::onClose));
        auto menu=CCMenu::create(); menu->setPosition({win.width/2,win.height/2-103}); menu->addChild(close); addChild(menu);
        return true;
    }
    void onClose(CCObject*) { removeFromParentAndCleanup(true); }
    void keyBackClicked() override { removeFromParentAndCleanup(true); }
};

class GeoBRCreatorHubPopup : public CCLayerColor {
public:
    static GeoBRCreatorHubPopup* create() {
        auto layer=new GeoBRCreatorHubPopup(); if(layer&&layer->init()){layer->autorelease();return layer;} CC_SAFE_DELETE(layer);return nullptr;
    }
    bool init() {
        if(!CCLayerColor::initWithColor({0,0,0,180})) return false;
        auto win=CCDirector::sharedDirector()->getWinSize(); setContentSize(win); setKeypadEnabled(true); setTouchEnabled(true);
        auto bg=CCScale9Sprite::create("GJ_square01.png",{0,0,80,80}); bg->setContentSize({500,330}); bg->setPosition({win.width/2,win.height/2}); addChild(bg);
        auto title=CCLabelBMFont::create("GEOBR CREATOR HUB","goldFont.fnt"); title->setPosition({win.width/2,win.height/2+128}); title->setScale(.9f); addChild(title);
        auto sub=CCLabelBMFont::create("FERRAMENTAS PARA CREATORS","chatFont.fnt"); sub->setPosition({win.width/2,win.height/2+101}); sub->setScale(.58f); sub->setOpacity(200); addChild(sub);
        addCard(win,"OBJETOS", "🧱 Biblioteca de objetos GeoBR", win.width/2-115, win.height/2+35);
        addCard(win,"TRIGGERS", "⚡ Novos triggers e ferramentas", win.width/2+115, win.height/2+35);
        addCard(win,"ANIMADOR", "🎬 Sistema de animação", win.width/2-115, win.height/2-50);
        addCard(win,"PACKS", "📦 Packs de criação", win.width/2+115, win.height/2-50);
        auto info=CCLabelBMFont::create("Creator Hub • novos recursos em desenvolvimento","chatFont.fnt"); info->setPosition({win.width/2,win.height/2-112}); info->setScale(.48f); info->setOpacity(170); addChild(info);
        auto closeSprite=CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"); closeSprite->setScale(.78f);
        auto close=CCMenuItemSpriteExtra::create(closeSprite,this,menu_selector(GeoBRCreatorHubPopup::onClose)); auto menu=CCMenu::create(); menu->setPosition({win.width/2,win.height/2-142}); menu->addChild(close); addChild(menu);
        return true;
    }
private:
    void addCard(CCSize win,const char* title,const char* desc,float x,float y){
        auto box=CCScale9Sprite::create("GJ_square02.png",{0,0,40,40}); box->setContentSize({205,72}); box->setPosition({x,y}); box->setOpacity(150); addChild(box);
        auto t=CCLabelBMFont::create(title,"bigFont.fnt"); t->setPosition({x,y+18}); t->setScale(.48f); addChild(t);
        auto d=CCLabelBMFont::create(desc,"chatFont.fnt"); d->setPosition({x,y-14}); d->setScale(.40f); d->setOpacity(190); addChild(d);
    }
    void onClose(CCObject*){removeFromParentAndCleanup(true);} void keyBackClicked() override{removeFromParentAndCleanup(true);}
};

class GeoBRHubPopup : public CCLayerColor {
public:
    static GeoBRHubPopup* create(){auto l=new GeoBRHubPopup();if(l&&l->init()){l->autorelease();return l;}CC_SAFE_DELETE(l);return nullptr;}
    bool init(){
        if(!CCLayerColor::initWithColor({0,0,0,170}))return false; auto win=CCDirector::sharedDirector()->getWinSize(); setContentSize(win);setKeypadEnabled(true);setTouchEnabled(true);
        auto bg=CCScale9Sprite::create("GJ_square01.png",{0,0,80,80});bg->setContentSize({460,300});bg->setPosition({win.width/2,win.height/2});addChild(bg);
        auto title=CCLabelBMFont::create("GEOBR","goldFont.fnt");title->setPosition({win.width/2,win.height/2+115});title->setScale(1);addChild(title);
        auto sub=CCLabelBMFont::create("CENTRAL DA COMUNIDADE","chatFont.fnt");sub->setPosition({win.width/2,win.height/2+88});sub->setScale(.62f);sub->setOpacity(210);addChild(sub);
        addButton(win,"NOTÍCIAS",win.width/2-118,win.height/2+18,menu_selector(GeoBRHubPopup::onNews));
        addButton(win,"PERFIL",win.width/2,win.height/2+18,menu_selector(GeoBRHubPopup::onSoon));
        addButton(win,"RANKING",win.width/2+118,win.height/2+18,menu_selector(GeoBRHubPopup::onSoon));
        auto hint=CCLabelBMFont::create("Mais recursos serão adicionados em breve","chatFont.fnt");hint->setPosition({win.width/2,win.height/2-77});hint->setScale(.52f);hint->setOpacity(175);addChild(hint);
        auto cs=CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");cs->setScale(.78f);auto c=CCMenuItemSpriteExtra::create(cs,this,menu_selector(GeoBRHubPopup::onClose));auto m=CCMenu::create();m->setPosition({win.width/2,win.height/2-113});m->addChild(c);addChild(m);return true;
    }
private:
    void addButton(CCSize win,const char* label,float x,float y,SEL_MenuHandler handler){auto s=CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");if(!s)return;s->setScale(1);auto b=CCMenuItemSpriteExtra::create(s,this,handler);auto m=CCMenu::create();m->setPosition({x,y});m->addChild(b);addChild(m);auto t=CCLabelBMFont::create(label,"bigFont.fnt");t->setPosition({x,y-53});t->setScale(.49f);addChild(t);}
    void onNews(CCObject*){auto p=GeoBRNewsPopup::create();if(p){getParent()->addChild(p,1000);removeFromParentAndCleanup(true);}}
    void onSoon(CCObject*){FLAlertLayer::create("GeoBR","Esta função estará disponível em uma próxima atualização.","OK")->show();}
    void onClose(CCObject*){removeFromParentAndCleanup(true);} void keyBackClicked()override{removeFromParentAndCleanup(true);}
};

class $modify(GeoBRMenuLayer, MenuLayer){
    bool init(){if(!MenuLayer::init())return false;auto menu=this->getChildByID("bottom-menu");if(!menu)return true;auto icon=CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");if(!icon)return true;icon->setScale(1);auto b=CCMenuItemSpriteExtra::create(icon,this,menu_selector(GeoBRMenuLayer::onGeoBR));b->setID("geobr-hub-button"_spr);menu->addChild(b);menu->updateLayout();return true;}
    void onGeoBR(CCObject*){auto p=GeoBRHubPopup::create();if(p)this->getParent()->addChild(p,1000);}
};

class $modify(GeoBREditorUI, EditorUI){
    bool init(LevelEditorLayer* editorLayer){
        if(!EditorUI::init(editorLayer)) return false;
        auto menu=this->getChildByID("editor-buttons");
        if(!menu) menu=this->getChildByID("bottom-menu");
        if(!menu){log::warn("GeoBR: menu do editor não encontrado");return true;}
        auto icon=CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"); if(!icon)return true;
        icon->setScale(.95f);
        auto button=CCMenuItemSpriteExtra::create(icon,this,menu_selector(GeoBREditorUI::onGeoBR));
        button->setID("geobr-editor-hub"_spr); menu->addChild(button); menu->updateLayout();
        log::info("GeoBR: Creator Hub adicionado ao Editor"); return true;
    }
    void onGeoBR(CCObject*){auto p=GeoBRCreatorHubPopup::create();if(p)this->getParent()->addChild(p,1000);}
};
