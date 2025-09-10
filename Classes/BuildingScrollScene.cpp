#include "BuildingScrollScene.h"
#include "BuildingScene.h"
#include "MiningScene.h"
#include "ShoppingScene.h"
#include "SellManager.h"
#include "UpgradeManager.h"
#include "User.h"
#include "UpgradeScene.h"
#include "MusicManager.h"

bool ScrollScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MusicManager::PlayBuilding();
    
    //다른씬으로 갈 수 있는 메뉴 설치
	Menu_create();

    //초기화
	EndDraw=false;
    
    makednumber=0;
    sell = SellManager::Calculate();

    Complete =new Popup();
    Complete->SetString("Sell Complete");
    Complete->Init();
    this->addChild(Complete->GetLayer(),100);
    
    auto backForm = Sprite::create("UI/upgradeNumber.png");
    backForm->setPosition(230,400);
    this->addChild(backForm,1);
    
    sellMoney=Label::createWithTTF(StringUtils::format("Value : %d",sell), "fonts/arial.ttf", 20);
    sellMoney->setPosition(230,400);
    sellMoney->setColor(Color3B::BLACK);
    this->addChild(sellMoney,2);
    
    sellButton = Sprite::create("UI/button2.png");
    sellButton->setScale(2.0f);
    sellButton->setPosition(250,350);
    this->addChild(sellButton,2);
    
    auto label=Label::createWithTTF("Sell", "fonts/arial.ttf", 20);
    label->setPosition(250,350);
    this->addChild(label,3);
    
    //스크롤 설치
	Built=Layer::create();
	Built->setContentSize(Size(320,10000));
	scroll=ScrollView::create(Size(320,480),Built);
	scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setBounceable(false);
    this->addChild(scroll,0);

    //Texture 설정
	one=TextureFactory::Create("Background/background2_1.png");
	two=TextureFactory::Create("Background/background2_2.png");
	three=TextureFactory::Create("Background/background2_3.png");

    //백그라운드 설치
	create_b();

    //리스너 설치
	auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ScrollScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ScrollScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //스케줄러 설치
	this->schedule(schedule_selector(ScrollScene::ChangeBack),0.5f);//백그라운드의 그림을 바꿔주는애
	this->schedule(schedule_selector(ScrollScene::drawdt),0.4f);//그림을 순차적으로 그려주는 애

    
    
    CCLOG("행성 가치 %d",sell);
    
    return true;
}
bool ScrollScene::onTouchBegan(Touch *touch,  Event * unused_event){
    if(Complete->OnThis)
        Complete->onTouchBegan(touch);
    if(sellButton->getBoundingBox().containsPoint(touch->getLocation())){
        sellButton->setOpacity(150);
    }
    return true;
    
}

void ScrollScene::onTouchEnded( Touch *touch,  Event * unused_event){
    sellButton->setOpacity(255);
    if(Complete->OnThis)
        Complete->onTouchEnded(touch);
    
    if(sellButton->getBoundingBox().containsPoint(touch->getLocation())&&sell!=0){
        for(Sprite* spr : drawed){
            spr->setVisible(false);
            this->removeChild(spr);
            Complete->on();
        }
        sellMoney->setString("Value : 0");
        CCLOG("%d",Defaultmanager::Money);
        Defaultmanager::Money+=sell;
        CCLOG("%d",Defaultmanager::Money);
        CCLOG("행성 가치 %d",sell);
        
        std::vector<InPlanet*> tmp;
        mUpgrade::In_Planet=tmp;
        mUpgrade::SaveThePlanet();
        UserDefault::getInstance()->setIntegerForKey("Money", Defaultmanager::Money);
    }
}
void ScrollScene::Touch_Setup(Ref* pSender)
{
    
    Director::getInstance()->replaceScene(UpgradeScene::createScene());

}
void ScrollScene::SpriteCr(int count)
{
    
    InPlanet * planet = mUpgrade::In_Planet.at(count);
    Change(planet->GetUpgrade(),planet->GetKind(),160,100+100*count);
}

void ScrollScene::Change(int Upgrade, int Kind, int x, int y)
{
    auto spr = Sprite::create(StringUtils::format("planet%d/%d.png", Kind, Upgrade));
    spr->setPosition(x,y);
    Built->addChild(spr);
    drawed.pushBack(spr);
}
//-------------------------------this is unchangable-----------------------------------------------//
void ScrollScene::ChangeBack(float dt)
{
    if(number==1)
    {
        for(int i=0;i<30;i++)
        {
            Background[i]->setTexture(i%3==0?one:i%3==1?two:three);
        }
        number=2;
    }else if(number==2)
    {
        for(int i=0;i<30;i++)
        {
            Background[i]->setTexture(i%3==0?two:i%3==1?three:one);
        }
        number=3;
    }
    else if(number==3)
    {
        for(int i=0;i<30;i++)
        {
            Background[i]->setTexture(i%3==0?three:i%3==1?one:two);
        }
        number=1;
    }
    
}
void ScrollScene::Menu_create()
{
    
    auto Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Building=Sprite::create("UI/Building.png");
    auto t_Upgrade=Sprite::create("UI/Upgrade.png");
    auto t_Mine=Sprite::create("UI/Mining.png");
    auto Mine=Sprite::create("UI/Mining.png");
    auto Upgrade=Sprite::create("UI/Upgrade.png");
    auto Building=Sprite::create("UI/Building.png");
    
    t_Building->setOpacity(150);
    t_Upgrade->setOpacity(150);
    t_Mine->setOpacity(150);
    t_Shop->setOpacity(150);

    auto _ui1=MenuItemSprite::create(Building,t_Building,Building,CC_CALLBACK_1(ScrollScene::Touch_building,this));
    auto _ui2=MenuItemSprite::create(Upgrade,t_Upgrade,Upgrade,CC_CALLBACK_1(ScrollScene::Touch_Setup,this));
    auto _ui3=MenuItemSprite::create(Mine,t_Mine,Mine,CC_CALLBACK_1(ScrollScene::Touch_Mine,this));
    auto _ui4=MenuItemSprite::create(Shop, t_Shop,Shop,CC_CALLBACK_1(ScrollScene::Touch_Shop, this));
    
    auto UI=Menu::create(_ui4,_ui3,_ui1,_ui2,NULL);
    UI->alignItemsHorizontallyWithPadding(5);
    UI->setPosition(233,458);
    
    this->addChild(UI,10);
    
    this->setKeypadEnabled(true);
    
}
void ScrollScene::drawdt(float dt)
{
    if(!EndDraw)
    {
        if(mUpgrade::In_Planet.size()==0)
            EndDraw=true;
        else
            SpriteCr(makednumber++);
        
        if(makednumber>=mUpgrade::In_Planet.size())
            EndDraw=true;
    }
}
void ScrollScene::Touch_Mine(Ref* pSender)
{
    Director::getInstance()->replaceScene(Mining::createScene());
}
void ScrollScene::Touch_building(Ref* pSender)
{
    Director::getInstance()->replaceScene(BuildingScene::createScene());
}
void ScrollScene::Touch_Shop(Ref* pSender)
{
    Director::getInstance()->replaceScene(ShoppingScene::createScene());
}
Scene* ScrollScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ScrollScene::create();
    
    scene->addChild(layer);
    
    return scene;
}
void ScrollScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        Director::getInstance()->replaceScene(BuildingScene::createScene());
    }
}
