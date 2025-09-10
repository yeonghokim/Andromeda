//
//  LoadingScene.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 10. 20..
//
//
#include "LoadingScene.h"
#include "UpgradeScene.h"

Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LoadingScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool LoadingScene::init(){

    if (!Layer::init())
        return false;
    
    for(int i=0;i<6;i++){
        auto spr = Sprite::create(StringUtils::format("UpgradeLoad/%d.png",i+1));
        texture[i]= spr->getTexture();

    }
    step=0;
    background=Sprite::createWithTexture(texture[0]);
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,-1000);
    
    Sprite* mSprite= Sprite::create("TimeAction/barInner.png");
    
    mProgresstimer =ProgressTimer::create(mSprite);
    mProgresstimer->setPercentage(100.0f);
    
    mProgresstimer->setType(ProgressTimer::Type::BAR);
    mProgresstimer->setMidpoint(Point(0, 0.5f));
    mProgresstimer->setBarChangeRate(Point(1, 0));
    mProgresstimer->setPosition(160,50);
    this->addChild(mProgresstimer,2);
    
    ProgressFromTo* action = ProgressFromTo::create(2.5, 100, 0);
    mProgresstimer->runAction(action);
    
    this->schedule(schedule_selector(LoadingScene::ChangeBack), 0.1f);
    this->scheduleUpdate();
    return true;
}
void LoadingScene::update(float dt){
    if(mProgresstimer->getPercentage()==0)
        Director::getInstance()->replaceScene(UpgradeScene::createScene());
}
void LoadingScene::ChangeBack(float dt){
    step++;
    background->setTexture(texture[step]);
    if(step>=5){
        step=-1;
    }
}
