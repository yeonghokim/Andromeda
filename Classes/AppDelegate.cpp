#include "AppDelegate.h"
#include "UpgradeScene.h"
#include "MiningScene.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    
    return 0; 
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("To Andromeda",Rect(0,0,320,520));

        director->setOpenGLView(glview);
    }
    ///////////////////////////////////////////////////////////////

    director->getOpenGLView()->setDesignResolutionSize(320,520,ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(false);

    director->setAnimationInterval(1.0 / 60);
    
    if(UserDefault::getInstance()->getIntegerForKey("IsXmlExit3")==0){//int
        
        UserDefault::getInstance()->setIntegerForKey("IsXmlExit3", 1);
        
        UserDefault::getInstance()->setStringForKey("version", "Ver1");
        
        UserDefault::getInstance()->setIntegerForKey("User_power",1);

        UserDefault::getInstance()->setIntegerForKey("User_lucky",1);
        
        UserDefault::getInstance()->setIntegerForKey("Labornum",1);
        
        UserDefault::getInstance()->setIntegerForKey("LaborPower",1);
        
        UserDefault::getInstance()->setIntegerForKey("MineUpgrade",1);
        
        UserDefault::getInstance()->setIntegerForKey("Money",0);
        
        UserDefault::getInstance()->setIntegerForKey("MineMoney",0);
           //쌓여진 행성의 강화계수저장  Kind 번호 upgrade
        
        UserDefault::getInstance()->setStringForKey("InUpgrade", "InUpgrade0000{}");
        
        UserDefault::getInstance()->setStringForKey("UpgradeData", "UpgradeData0000{}");//Kind Upgrade
        
        
        //인벤토리 저장 및 강화계수 저장
    }
    
    mUpgrade::GetInventory();
    mUpgrade::GetThePlanet();
    
    register_all_packages();
    
	auto scene = MainScene::createScene();
		
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
