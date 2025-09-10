
//
//  UpgradeScene.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 26..
//
//
#include "UpgradeScene.h"
#include "LoadingScene.h"
#include "MiningScene.h"
#include "BuildingScene.h"
#include "ShoppingScene.h"

#include "MusicManager.h"

bool UpgradeScene::ReturnBack=false;
int UpgradeScene::step=0;

Scene* UpgradeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = UpgradeScene::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool UpgradeScene::init(){
    
    if (!Layer::init())
        return false;
    
    MusicManager::PlayUpgrade();
    
    NoMoney= new Popup();
    NoMoney->SetString("No Money");
    NoMoney->Init();
    this->addChild(NoMoney->GetLayer(),1000000);
    
    if(ReturnBack){
        Upgrademanager= new mUpgrade();
        int upg = mUpgrade::Inventory_Planet.at(step)->GetUpgrade();
        int percent = 100-(upg-1)*10;
        
        DelayTime* delay = DelayTime::create(0.5f);
        FadeOut* fadeout = FadeOut::create(1.0);
        Sequence* sequence =Sequence::create(delay,fadeout, NULL);
        Sprite* spr;
        if(RandomHelper::random_int(1, 100)<=percent){
            //성공
            spr = Sprite::create("UpgradeScene/success.png");
            
            CCLOG("step : %d",step);
                Upgrademanager->upgradePlanet(step);
                step =(int)mUpgrade::Inventory_Planet.size()-1;
            if(step<0) step = 0;
            
        }else{
            //실패
            spr = Sprite::create("UpgradeScene/fail.png");
        }
        spr->setPosition(160,240);
        this->addChild(spr,100000);
        spr->runAction(sequence);
    }
    
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(UpgradeScene::onTouchBegan, this);
    
    listener->onTouchEnded = CC_CALLBACK_2(UpgradeScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    background = Sprite::create("Background/background3.png");
    background -> setPosition(160,240);
    this->addChild(background);
    
    ShowUpgrade=Label::createWithTTF("", "fonts/arial.ttf", 25);
    ShowUpgrade->setPosition(160,205);
    ShowUpgrade->setColor(Color3B::BLACK);
    this->addChild(ShowUpgrade,1);
    
    auto BackForm = Sprite::create("UI/upgradeNumber.png");
    BackForm->setScaleY(1.5f);
    BackForm->setPosition(160,200);
    this->addChild(BackForm,0);
    
    
    if(mUpgrade::Inventory_Planet.size()!=0)
    {
        mars = Sprite::create("planet1/1.png");
        mars -> setPosition(160,270);
        this->addChild(mars);
        Change(mUpgrade::Inventory_Planet.at(step)->GetUpgrade(),mUpgrade::Inventory_Planet.at(step)->GetKind());
        Selected=true;
        
        MoneyLabel = Label::createWithTTF("", "fonts/arial.ttf", 15);
        MoneyLabel ->setAnchorPoint(Point(0,0.5));
        MoneyLabel->setPosition(150,185);
        MoneyLabel->setColor(Color3B::BLACK);
        this->addChild(MoneyLabel,2);
        
        if(mUpgrade::Inventory_Planet.at(step)->GetUpgrade()==5){
            ShowUpgrade->setString("+5");
            MoneyLabel->setString("Upgrade complete");
        }
        else{
            ShowUpgrade->setString(StringUtils::format("+%d -> +%d",mUpgrade::Inventory_Planet.at(step)->GetUpgrade(),mUpgrade::Inventory_Planet.at(step)->GetUpgrade()+1));
            MoneyLabel->setString(StringUtils::format("%d",(int)(
                                                                 (mUpgrade::Inventory_Planet.at(step)->GetUpgrade()==0?1.5:1)
                                                                 *mUpgrade::Inventory_Planet.at(step)->GetUpgrade()*500
                                                                 *mUpgrade::Inventory_Planet.at(step)->GetKind()
                                                                 )
                                                      )
                                  );
        }
        
        auto coin = Sprite::create("Ui/coin.png");
        coin->setPosition(125,185);
        coin->setScale(0.5);
        this->addChild(coin,2);
        
    }
    else
    {
        Label* label = Label::createWithTTF("No Planet", "fonts/arial.ttf", 20);
        label->setPosition(160,270);
        this->addChild(label);
        Selected=false;
    }
    
    left = Sprite::create("UpgradeScene/button.png");
    left->setPosition(80,270);
    this->addChild(left);
    
    right = Sprite::create("UpgradeScene/button1.png");
    right->setPosition(250,270);
    this->addChild(right);
    
    UpgradeButton =Sprite::create("UpgradeScene/upgradeButton.png");
    UpgradeButton->setPosition(160,140);
    this->addChild(UpgradeButton);
    
    Menu_create();
    
    this->setKeypadEnabled(true);
    
    return true;

}
bool UpgradeScene::onTouchBegan(Touch* touch, Event* event)
{
    if(NoMoney->OnThis){
        NoMoney->onTouchMoved(touch);
        return true;
    }
    return true;
}
void UpgradeScene::onTouchEnded(Touch* touch, Event* event)
{
    if(NoMoney->OnThis){
        NoMoney->onTouchEnded(touch);
        return;
    }
    if(Selected&&UpgradeButton->getBoundingBox().containsPoint(touch->getLocation())&&mUpgrade::Inventory_Planet.at(step)->GetUpgrade()==5){
        //최대 업그레이드 계수
        return;
    }
    if(right->getBoundingBox().containsPoint(touch->getLocation())){
        RightB();
    }
    if(left->getBoundingBox().containsPoint(touch->getLocation())){
        LeftB();
    }
    if(Selected&&UpgradeButton->getBoundingBox().containsPoint(touch->getLocation())){
        ReturnBack=true;
        if(Defaultmanager::Money>=std::atoi(MoneyLabel->getString().c_str())){
            CCLOG("%d",Defaultmanager::Money);
            Defaultmanager::Money=Defaultmanager::Money-std::atoi(MoneyLabel->getString().c_str());
            CCLOG("%d",Defaultmanager::Money);
        }else{
            NoMoney->on();
            return;
        }
        UserDefault::getInstance()->setIntegerForKey("Money",Defaultmanager::Money);
        
        
        Director::getInstance()->replaceScene(LoadingScene::createScene());
    }
}
void UpgradeScene::Change(int Upgrade, int Kind)
{
    auto spr = Sprite::create(StringUtils::format("planet%d/%d.png", Kind, Upgrade));
    mars->setTexture(spr->getTexture());
}
void UpgradeScene::PlanetChange()
{
    Planet* planet = mUpgrade::Inventory_Planet.at(step);
    Change(planet->GetUpgrade(), planet->GetKind());
    
    if(mUpgrade::Inventory_Planet.at(step)->GetUpgrade()==5){
        ShowUpgrade->setString("+5");
    }
    else{
        ShowUpgrade->setString(StringUtils::format("+%d -> +%d",mUpgrade::Inventory_Planet.at(step)->GetUpgrade(),mUpgrade::Inventory_Planet.at(step)->GetUpgrade()+1));
    }
    
}
void UpgradeScene::RightB()
{
    
    if (step+1 < mUpgrade::Inventory_Planet.size())
    {
        step++;
        PlanetChange();
    }
    else {
        //안되게 해주는 액션
    }
}
void UpgradeScene::LeftB()
{
    if (step > 0)
    {
        step--;
        PlanetChange();
    }
    else {
        //안되게 해주는 액션
    }
}
void UpgradeScene::Touch_book(Ref* pSender){
    
    
}
void UpgradeScene::Touch_Build(Ref* pSender){
    mUpgrade::SaveInventory();
    ReturnBack=false;
    Director::getInstance()->replaceScene(BuildingScene::createScene());
    
}
void UpgradeScene::Touch_Mine(Ref* pSender){
    mUpgrade::SaveInventory();
    ReturnBack=false;
    Director::getInstance()->replaceScene(Mining::createScene());
    
}
void UpgradeScene::Touch_Shop(Ref* pSender){
    mUpgrade::SaveInventory();
    ReturnBack=false;
    Director::getInstance()->replaceScene(ShoppingScene::createScene());
}
void UpgradeScene::Menu_create()
{
    auto Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Book=Sprite::create("UI/Book.png");
    auto t_Build=Sprite::create("UI/Building.png");
    auto t_Mine=Sprite::create("UI/Mining.png");
    auto Mine=Sprite::create("UI/Mining.png");
    auto Build=Sprite::create("UI/Building.png");
    auto Book=Sprite::create("UI/Book.png");
    t_Shop->setOpacity(150);
    t_Book->setOpacity(150);
    t_Build->setOpacity(150);
    t_Mine->setOpacity(150);
    
    auto _ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(UpgradeScene::Touch_book,this));
    auto _ui2=MenuItemSprite::create(Build ,t_Build,Build,CC_CALLBACK_1(UpgradeScene::Touch_Build,this));
    auto _ui3=MenuItemSprite::create(Mine,t_Mine,Mine,CC_CALLBACK_1(UpgradeScene::Touch_Mine,this));
    auto _ui4=MenuItemSprite::create(Shop, t_Shop,Shop,CC_CALLBACK_1(UpgradeScene::Touch_Shop, this));
    
    Menu* UI=Menu::create(_ui4,_ui3,_ui1,_ui2,NULL);
    UI->alignItemsHorizontallyWithPadding(5);
    UI->setPosition(233,458);
    
    this->addChild(UI,100);
}

void UpgradeScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        Director::getInstance()->replaceScene(Mining::createScene());
    }
}
