//
//  MainScene.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 11. 10..
//
//

#include "MainScene.h"
#include "MusicManager.h"
#include "MiningScene.h"

#define Max_Category 0

Scene* MainScene::createScene()
{
    
    auto scene = Scene::create();
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

void MainScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        Director::getInstance()->end();
    }
}

bool MainScene::init(){
    
    if(!Layer::init())
    {
        return false;
    }
    MusicManager::PlayMenu();
    mTouchNumber=0;
    
    mBackground= Sprite::create("Main/BackGround.png");
    mBackground->setAnchorPoint(Point(0,0));
    mBackground->setScale(0.25);
    this->addChild(mBackground,0);
    
    mMainRect = Sprite::create("Main/MainRect.png");
    mMainRect->setPosition(160,240);
    mMainRect->setScale(0.3);
    this->addChild(mMainRect,1);
    
    mLeft=Sprite::create("Main/LeftTriangle.png");
    mLeft->setAnchorPoint(Point(0,0.5));
    mLeft->setPosition(75,240);
    mLeft->setScale(0.25);
    this->addChild(mLeft,1);
    
    mRight=Sprite::createWithTexture(mLeft->getTexture());
    mRight->setAnchorPoint(Point(1,0.5));
    mRight->setPosition(230,240);
    mRight->setRotation(180);
    mRight->setScale(0.25);
    this->addChild(mRight,1);
    
    auto label =Label::createWithTTF("ToAndromeda", "Main/Delta_Universe.ttf", 65);
    label ->setAnchorPoint(Point(0,0.5));
    label->setPosition(10,140);
    label->enableGlow(Color4B::WHITE);
    this->addChild(label,1);
    
    mLabel = Label::createWithTTF("Start", "fonts/KoPubDotumBold.ttf", 20);
    mLabel->setPosition(160,240);
    mLabel->setAlignment(TextHAlignment::CENTER);
    this->addChild(mLabel,2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    this->setKeypadEnabled(true);
    return true;
}
bool MainScene::onTouchBegan(Touch* touch, Event* unused_event){
    
    return true;
}
void MainScene::onTouchEnded(Touch* touch, Event* unused_event){
    if(mLeft->getBoundingBox().containsPoint(touch->getLocation())){
        
        mTouchNumber--;
        if(mTouchNumber<0) mTouchNumber=0;
        
    }else if(mRight->getBoundingBox().containsPoint(touch->getLocation())){
        
        mTouchNumber++;
        if(mTouchNumber>Max_Category) mTouchNumber=Max_Category;
        
    }else if(mMainRect->getBoundingBox().containsPoint(touch->getLocation())){
        switch (mTouchNumber) {
            case 0:
                Director::getInstance()->replaceScene(Mining::createScene());
                break;
                
            case 1:
                
                break;
                
            default:
                break;
        }
        return;
    }
    switch (mTouchNumber) {
        case 0:
            mLabel->setString("Start");
            break;
        case 1:
            mLabel->setString("Buy\nAndromeda");
            break;
        default:
            break;
    }
    
}
