#include "ShoppingScene.h"
#include "BuildingScene.h"
#include "MiningScene.h"
#include "UpgradeManager.h"
#include "UpgradeScene.h"
#include "MusicManager.h"

Scene* ShoppingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ShoppingScene::create();

    scene->addChild(layer);

    return scene;
}
ShoppingScene::ShoppingScene(){
    upPlanet=-1;
}
ShoppingScene::~ShoppingScene(){
    
}
void ShoppingScene::Touch_book(Ref* pSender){
    Mining::Savingmanager->Saving();
}


void ShoppingScene::Touch_Setup(Ref* pSender){
    Mining::Savingmanager->Saving();
    Director::getInstance()->replaceScene(UpgradeScene::createScene());
}

void ShoppingScene::Touch_Building(Ref* pSender){
    Mining::Savingmanager->Saving();
    Director::getInstance()->replaceScene(BuildingScene::createScene());
}

void ShoppingScene::Touch_Mine(Ref* pSender){
    Mining::Savingmanager->Saving();
    Director::getInstance()->replaceScene(Mining::createScene());
}

bool ShoppingScene::init(){
    
	if (!Layer::init()) return false;
    MusicManager::PlayShopping();
    
    NoMoney=new Popup();
    NoMoney->SetString("No Money");
    NoMoney->Init();
    this->addChild(NoMoney->GetLayer(),6);
    
    SellComplete= new Popup();
    SellComplete->SetString("Complete");
    SellComplete->Init();
    this->addChild(SellComplete->GetLayer(),6);
    
    int UpgradeNum = UserDefault::getInstance()->getIntegerForKey("MineUpgrade");
    
    animate_stack=0;
    background=Sprite::create("Background/background2_1.png");
    background->setAnchorPoint(Point(0,0));
    this->addChild(background,0);
    
    animation[0]=background->getTexture();
    animation[1]=Sprite::create("Background/background2_2.png")->getTexture();
    animation[2]=Sprite::create("Background/background2_3.png")->getTexture();

    auto colorback =LayerColor::create(Color4B::WHITE);
    colorback->setContentSize(Size(320,186));
    colorback->setAnchorPoint(Point(0,0));
    this->addChild(colorback,1);
    
    auto lay = Layer::create();
    lay->setContentSize(Size(280.0*5/3.0,280));
    
    auto spr=Sprite::create("UI/ShopBottom.png");
    spr->setAnchorPoint(Point(0,0));
    spr->setPosition(0,0);
    lay->addChild(spr);
    
    scroll=ScrollView::create(Size(480,186));
    scroll->setViewSize(Size(320,186));
    scroll->setAnchorPoint(Point(0,0));
    scroll->setContainer(lay);
    scroll->setBounceable(false);
    scroll->setDirection(ScrollView::Direction::HORIZONTAL);
    this->addChild(scroll,2);
    
    Label* moneylabel =Label::createWithTTF(StringUtils::format("%d",Defaultmanager::MineMoney),"fonts/arial.ttf", 20);
    moneylabel->setColor(Color3B::BLACK);
    moneylabel->setPosition(80,453);
    moneylabel->setTag(10000);
    this->addChild(moneylabel,4);
    
    auto MoneySprite = Sprite::create("UI/money box.png");
    MoneySprite->setPosition(7,478);
    MoneySprite->setAnchorPoint(Point(0,1));
    MoneySprite->setScale(0.9f);
    this->addChild(MoneySprite,3);
    
    auto minesprite = Sprite::create("UI/Mining.png");
    minesprite->setPosition(27,455);
    minesprite->setScale(0.9);
    this->addChild(minesprite,4);
    
    BuyButton=Sprite::create("UI/ShopButton.png");
    BuyButton->setPosition(220,340);
    this->addChild(BuyButton,3);
    
    auto coin =Sprite::create("UI/Money.png");
    coin->setPosition(220,300);
    coin->setScale(0.8);
    this->addChild(coin,3);
    
    SellMoney= Label::createWithTTF("0", "fonts/arial.ttf", 20);
    SellMoney->setPosition(220,300);
    SellMoney->setColor(Color3B::BLACK);
    this->addChild(SellMoney,4);
    
    for(int i=0;i<UpgradeNum;i++){
        spr=Sprite::create(StringUtils::format("planet%d/1.png",i+1));
        spr->setScale(0.8);
        spr->setPosition(47+(i/2)*90+(i/2)*3,i%2==0?140:50);
        lay->addChild(spr,3);
        Planets.pushBack(spr);
    }

    moll=Sprite::create("Character/moll.png");
    moll->setFlippedX(true);
    moll->setPosition(300,210);
    moll->setScale(0.8);
    this->addChild(moll,4);
    
    auto Mine=Sprite::create("UI/Mining.png");
    auto t_Mine=Sprite::create("UI/Mining.png");
    auto Book=Sprite::create("UI/Book.png");
    auto t_Book=Sprite::create("UI/Book.png");
    auto Upgrade=Sprite::create("UI/Upgrade.png");
    auto t_Upgrade=Sprite::create("UI/Upgrade.png");
    auto Building=Sprite::create("UI/Building.png");
    auto t_Building=Sprite::create("UI/Building.png");
    Building->setAnchorPoint(Point(0,0));
    t_Building->setAnchorPoint(Point(0,0));
    t_Book->setOpacity(150);
    t_Upgrade->setOpacity(150);
    t_Building->setOpacity(150);
    t_Mine->setOpacity(150);
    
    auto _ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(ShoppingScene::Touch_book,this));
    auto _ui2=MenuItemSprite::create(Upgrade,t_Upgrade,Upgrade,CC_CALLBACK_1(ShoppingScene::Touch_Setup,this));
    auto _ui3=MenuItemSprite::create(Building,t_Building,Building,CC_CALLBACK_1(ShoppingScene::Touch_Building,this));
    auto _ui4=MenuItemSprite::create(Mine, t_Mine,Mine,CC_CALLBACK_1(ShoppingScene::Touch_Mine, this));
    auto UI=Menu::create(_ui4,_ui3,_ui1,_ui2,NULL);
    UI->alignItemsHorizontallyWithPadding(5);
    //UI->setAnchorPoint(Point(1,1));
    UI->setPosition(233,458);
    
    this->addChild(UI,100);
    
    //46
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(ShoppingScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(ShoppingScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(ShoppingScene::onTouchEnded,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(ShoppingScene::ChangeImage),0.5);
    
    this->setKeypadEnabled(true);
    
	return true;
}
void ShoppingScene::ChangeImage(float dt){
    animate_stack++;
    if(animate_stack>2) animate_stack=0;
    background->setTexture(animation[animate_stack]);
}
bool ShoppingScene::onTouchBegan(Touch* touch, Event* event)
{
    if(NoMoney->OnThis){
        NoMoney->onTouchEnded(touch);
        return true;
    }else if(SellComplete->OnThis){
        SellComplete->onTouchEnded(touch);
        return true;
    }
    if(BuyButton->getBoundingBox().containsPoint(touch->getLocation())){
        BuyButton->setOpacity(150);
    }
    return true;
}
void ShoppingScene::onTouchMoved(Touch* touch, Event* event){
	

}
void ShoppingScene::onTouchEnded(Touch* touch, Event* event){
    if(NoMoney->OnThis){
        NoMoney->onTouchEnded(touch);
        return;
    }else if(SellComplete->OnThis){
        SellComplete->onTouchEnded(touch);
        return;
    }
    
    
    BuyButton->setOpacity(255);
    if(BuyButton->getBoundingBox().containsPoint(touch->getLocation())){
        if(uponSprite!=nullptr&&upPlanet!=(-1)){
            if(Defaultmanager::MineMoney>=std::atoi(SellMoney->getString().c_str())){
                std::vector<Planet*>* tmpvector = &mUpgrade::Inventory_Planet;
                for(Planet* mPlanet : *tmpvector){
                    if(mPlanet->GetKind()==upPlanet+1&&mPlanet->GetUpgrade()==1){
                        
                        mPlanet->addPlanet();
                        Defaultmanager::MineMoney-=std::atoi(SellMoney->getString().c_str());
                        
                        //구매 완료
                        SellComplete->on();
                        Label* label = (Label*)this->getChildByTag(10000);
                        label->setString(StringUtils::format("%d",Defaultmanager::MineMoney));
                        return;
                    }
                }
                Planet* planet = new Planet(upPlanet+1,1,1);
                tmpvector->push_back(planet);
                Defaultmanager::MineMoney-=std::atoi(SellMoney->getString().c_str());
                
                //구매 완료
                SellComplete->on();
                Label* label = (Label*)this->getChildByTag(10000);
                label->setString(StringUtils::format("%d",Defaultmanager::MineMoney));
            }else{
                //돈이 없음
                NoMoney->on();
                
            }
        }
    }
    int tmp=0;
    for(Sprite* spr:Planets){
        Rect rect = spr->getBoundingBox();
        
        rect=Rect(rect.getMinX()+scroll->getContentOffset().x,rect.getMinY(),rect.size.width,rect.size.height);
        
        if(rect.containsPoint(touch->getLocation())){
            if(uponSprite==nullptr){
                uponSprite=Sprite::createWithTexture(spr->getTexture());
                uponSprite->setPosition(100,330);
                this->addChild(uponSprite,1);
            }else{
                uponSprite->setTexture(spr->getTexture());
            }
            SellMoney->setString(StringUtils::format("%d",(tmp*tmp+5)/2));
            upPlanet=tmp;
            return;
        }
        tmp++;
    }

    
}
void ShoppingScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        Director::getInstance()->replaceScene(Mining::createScene());
    }
}
