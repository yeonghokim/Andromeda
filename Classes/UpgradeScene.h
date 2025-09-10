//
//  UpgradeScene.h
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 26..
//
//
#pragma once

#include "cocos2d.h"
#include "Popup.h"
#include "UpgradeManager.h"

USING_NS_CC;

class UpgradeScene : public Layer{
private:
    void Change(int Upgrade, int Kind);
    void PlanetChange();
    
    bool Selected;
    
    void RightB();
    void LeftB();
    
    mUpgrade* Upgrademanager;
    
    Label* ShowUpgrade;
    
    Label* ShowMoney;
    
public:
    void Touch_book(Ref* pSender);
    void Touch_Build(Ref* pSender);
    void Touch_Mine(Ref* pSender);
    void Touch_Shop(Ref* pSender);
    
    void Menu_create();
    
    static int step;
    static bool ReturnBack;//처음 들어올땐 false 강화하고 들어올땐 true
    
    static Scene* createScene();
    
    virtual bool init();
    
    Sprite *background;
    Sprite *mars;
    Sprite *left;
    Sprite *right;
    
    Sprite* UpgradeButton;
    Label* MoneyLabel;
    
    Popup* NoMoney;
    
    
    EventListenerTouchOneByOne* listener;
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
    
    void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event );

    
    CREATE_FUNC(UpgradeScene);
};
