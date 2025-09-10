#include "MiningScene.h"
#include "UpgradeScene.h"
#include "ShoppingScene.h"
#include "BuildingScene.h"
#include "AdmobHelper.h"
#include "MusicManager.h"
#include "MainScene.h"



User* Mining::m_user=nullptr;
Defaultmanager* Mining::Savingmanager=nullptr;
void Mining::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Mining::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
		Savingmanager->Saving();
        Director::getInstance()->replaceScene(MainScene::createScene());
	}
}

Mining::Mining()
{
    
    if(Savingmanager==nullptr){
        Savingmanager=new Defaultmanager();
        Savingmanager->AddSaver("User_power",&(Defaultmanager::UserPower));
        Savingmanager->AddSaver("User_lucky",&(Defaultmanager::UserLucky));
        Savingmanager->AddSaver("MineUpgrade",&Defaultmanager::MinerLevel);
        Savingmanager->AddSaver("Labornum",&Defaultmanager::LaborNumber);
        Savingmanager->AddSaver("LaborPower",&Defaultmanager::LaborPower);
        Savingmanager->AddSaver("Money",&Defaultmanager::Money);
        Savingmanager->AddSaver("MineMoney",&Defaultmanager::MineMoney);
        Savingmanager->GetData();
    }

	for(int i=0;i<8;i++)
    {
		labor[i]=new Labor();
		labor_on[i]=false;
	}
    if(m_user==nullptr)
        m_user= new User(&Defaultmanager::Money);
}

Mining::~Mining()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

Scene* Mining::createScene()
{
	auto scene = Scene::create();
    
    auto layer = Mining::create();

    scene->addChild(layer);

    return scene;
}

bool Mining::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    MusicManager::PlayMining();
    
    AdmobHelper::showAd();
    
    mNoMoney= new Popup();
    mNoMoney->SetString("No Money");
    mNoMoney->Init();
    this->addChild(mNoMoney->GetLayer(),1000000);
    
    _touchAni=new TAnimation();
    _touchAni->InitTexture();
    _touchAni->SetLayer(this);
    

    //세이빙 객체
	if(!Savingmanager->GetData()) return false;
    

    
    for(int i=0;i<Defaultmanager::LaborNumber;i++)
    {
        labor_on[i]=true;
        add_labor(i);
        labor[i]->ChangeBool();
    }

    //시간 계산
	HealthBar =Sprite::create("UI/Time/timebar.png");
	HealthBar->setPosition(5,450);
	HealthBar->setAnchorPoint(Point(0,0.5));
    HealthBar->setScaleX((float)Defaultmanager::MinesHealth/(float)Defaultmanager::MaxHealth);
	this->addChild(HealthBar,ui);
	
	auto timeOutline=Sprite::create("UI/Time/timeoutline.png");
	timeOutline->setPosition(70,450);
	this->addChild(timeOutline,ui);

    Sprite* mMoneyBack = Sprite::create("UI/Money.png");
    mMoneyBack->setPosition(70,420);
    mMoneyBack->setScale(0.8);
    mMoneyBack->setOpacityModifyRGB(true);
    mMoneyBack->setOpacity(220);
    this->addChild(mMoneyBack,ui-1);
    
    mMoneyLabel = Label::createWithTTF(StringUtils::format("%d",Defaultmanager::Money), "fonts/arial.ttf", 15);
    mMoneyLabel->setPosition(70,420);
    mMoneyLabel->setColor(Color3B::BLACK);
    this->addChild(mMoneyLabel,ui);
    
	Background_create();
	Scroll_create();

	B_manager=new BottomManager();
	B_manager->Setting();
	B_manager->AddSprite(Mine);

	Menu_create();
	Label_create();

	listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
	listener->onTouchBegan = CC_CALLBACK_2(Mining::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Mining::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    Defaultmanager::SetNewMine();
    
	MineHealths=Label::createWithTTF("0","fonts/arial.ttf",20);
    MineHealths->setString(StringUtils::format("%d",Defaultmanager::MinesHealth));
	MineHealths->setColor(Color3B::WHITE);
	MineHealths->setPosition(70,470);
	this->addChild(MineHealths,ui);

    this->setKeypadEnabled(true);
	
    this->schedule(schedule_selector(Mining::labor_texture), 0.25);
    this->scheduleUpdate();

    return true;

}
void Mining::SetNewMine()
{
	Defaultmanager::SetNewMine();
}

void Mining::update(float dt)
{
	if(Defaultmanager::MinesHealth>0)
    {
		MineHealths->setString(StringUtils::format("%d",Defaultmanager::MinesHealth));
		HealthBar->setScaleX((float)Defaultmanager::MinesHealth/(float)Defaultmanager::MaxHealth);
	}
	else
    {
		MineHealths->setString("0");
		HealthBar->setScaleX(0);
        Defaultmanager::MineMoney++;
        Defaultmanager::MineMoney+=(Defaultmanager::UserLucky-1);

		return SetNewMine();
	}
}
void Mining::add_labor(int number)
{
//노동자 추가 메소드
	labor[number]->init();
	std::string tmps;
	switch(number)
    {
        case 0: tmps="Labor/labor1";
            this->addChild(labor[0]->layer_labor,mine_layer0);break;
        case 1: tmps="Labor/labor2";
            this->addChild(labor[1]->layer_labor,mine_layer1);break;
        case 2: tmps="Labor/labor1";
            this->addChild(labor[2]->layer_labor,mine_layer2);break;
        case 3: tmps="Labor/labor2";
            this->addChild(labor[3]->layer_labor,mine_layer3);break;
        case 4: tmps="Labor/labor1"; 
            this->addChild(labor[4]->layer_labor,mine_layer4);break;
        case 5: tmps="Labor/labor2";
            this->addChild(labor[5]->layer_labor,mine_layer5);break;
        case 6: tmps="Labor/labor1";
            this->addChild(labor[6]->layer_labor,mine_layer6);break;
        case 7: tmps="Labor/labor2";
            this->addChild(labor[7]->layer_labor,mine_layer6);break;
	}
    labor[number]->setnumber(number+1);
	labor[number]->setTexture(tmps);
	labor[number]->Add();
}

void Mining::labor_texture(float dt)
{
	for(int i=0;i<8;i++)
    {
		if(labor_on[i])
			labor[i]->texture_update(dt);
	}
}

bool Mining::onTouchBegan(Touch* touch, Event* unused_event)
{
    if(mNoMoney->OnThis){
        mNoMoney->onTouchMoved(touch);
        return true;
    }
	
	if(Rect(0,0,320,240).containsPoint(touch->getLocation()))
    {
		B_manager->onTouchBegan(touch,Mine_scroll,DEVELOPER);
	}
	if(Rect(0,240,320,480).containsPoint(touch->getLocation()))
    {
		m_user->Touched(touch);
	}
	return true;
}

void Mining::onTouchEnded(Touch* touch, Event* unused_event)
{
    if(mNoMoney->OnThis){
        mNoMoney->onTouchEnded(touch);
        return;
    }
    
    B_manager->u_Button->Power1->setOpacity(255);
    B_manager->u_Button->Power->setOpacity(255);
    B_manager->u_Button->People->setOpacity(255);
    B_manager->u_Button->Upgrade->setOpacity(255);
    B_manager->u_Button->Lucky->setOpacity(255);
    
    if(Rect(0,0,320,240).containsPoint(touch->getLocation()))//아랫 업그레이드 바 터치시
	{
		Rect r[5];
		r[4]=B_manager->u_Button->Lucky->getBoundingBox();
		r[3]=B_manager->u_Button->Power->getBoundingBox();
		r[2]=B_manager->u_Button->Upgrade->getBoundingBox();
		r[1]=B_manager->u_Button->People->getBoundingBox();
		r[0]=B_manager->u_Button->Power1->getBoundingBox();

		
		Rect scroll_rect[5];
		for(int i=0;i<5;i++)
            scroll_rect[i]=Rect(r[i].origin.x+Mine_scroll->getContentOffset().x,
                                r[i].origin.y+Mine_scroll->getContentOffset().y,
                                r[i].size.width,
                                r[i].size.height
                                );

		if(scroll_rect[4].containsPoint(touch->getLocation()))
		{
            if(Defaultmanager::UserLucky<MAX_LUCKY){
                if(m_user->MinusMoney(Defaultmanager::UserLucky*5000)){
                    mMoneyLabel->setString(StringUtils::format("%d",*m_user->Money));
                    Up_Lucky();
                    Lv[4]->setString(StringUtils::format("Lv%d",Defaultmanager::UserLucky));
                }else{
                    CCLOG("돈이 없습니다");
                    mNoMoney->on();
                }
            }
		}
        else if(scroll_rect[3].containsPoint(touch->getLocation()))
		{
            if(Defaultmanager::UserPower<MAX_POWER){
                if(m_user->MinusMoney(Defaultmanager::UserPower*1000)){
                    Up_Power(0);
                     mMoneyLabel->setString(StringUtils::format("%d",*m_user->Money));
                    Lv[3]->setString(StringUtils::format("Lv%d",Defaultmanager::UserPower));
                }else{
                    CCLOG("돈이 없습니다");
                    mNoMoney->on();
                }
            }
		}
        else  if(scroll_rect[2].containsPoint(touch->getLocation()))
		{
            if(Defaultmanager::MinerLevel<MAX_UPGRADENUM)
            {
                if(m_user->MinusMoney(Defaultmanager::MinerLevel*5000+Defaultmanager::MinerLevel*Defaultmanager::MinerLevel*500)){
                    Up_Upgrade();
                     mMoneyLabel->setString(StringUtils::format("%d",*m_user->Money));
                    Lv[2]->setString(StringUtils::format("Lv%d",Defaultmanager::MinerLevel));
                }else{
                    CCLOG("돈이 없습니다");
                    //팝업
                    mNoMoney->on();
                }
            }
		}
        else if(scroll_rect[1].containsPoint(touch->getLocation()))
		{
            if(Defaultmanager::LaborNumber<=MAX_PEOPLENUM)
            {
                
                if(m_user->MinusMoney((Defaultmanager::LaborNumber+1)*20000)){
                    Up_People();
                    Lv[1]->setString(StringUtils::format("Lv%d",Defaultmanager::LaborNumber+1));
                     mMoneyLabel->setString(StringUtils::format("%d",*m_user->Money));
                }else{
                    CCLOG("돈이 없습니다");
                    //팝업
                    mNoMoney->on();
                }
            }
		}
        else if(scroll_rect[0].containsPoint(touch->getLocation())&&labor_on[0])
		{
            if(Defaultmanager::LaborPower<MAX_POWER){
                if(m_user->MinusMoney((Defaultmanager::LaborPower<30)?Defaultmanager::LaborPower*2000:Defaultmanager::LaborPower*2500+500)){
                    Up_Power(1);
                     mMoneyLabel->setString(StringUtils::format("%d",*m_user->Money));
                    Lv[0]->setString(StringUtils::format("Lv%d",Defaultmanager::LaborPower));
                }else{
                    CCLOG("돈이 없습니다");
                    //팝업
                    mNoMoney->on();
                }
            }
		}
        WantMoney[4]->setString(StringUtils::format("%d",Defaultmanager::UserLucky*5000));
        WantMoney[3]->setString(StringUtils::format("%d",Defaultmanager::UserPower*1000));
        WantMoney[2]->setString(StringUtils::format("%d",Defaultmanager::MinerLevel*5000+Defaultmanager::MinerLevel*Defaultmanager::MinerLevel*500));
        WantMoney[1]->setString(StringUtils::format("%d",Defaultmanager::LaborNumber*20000+20000));
        WantMoney[0]->setString(StringUtils::format("%d",Defaultmanager::LaborPower*2000));
    }
    else if(Rect(0,240,320,480).containsPoint(touch->getLocation()))//위에 광산 터치시
    {
        _touchAni->TouchAnimation(touch);
    }
}

void Mining::Touch_book(Ref* pSender)
{
    Savingmanager->Saving();
	CCLOG("book");
	Savingmanager->Saving();
}
void Mining::Touch_Upgrade(Ref* pSender)
{
    Savingmanager->Saving();
    Director::getInstance()->replaceScene(UpgradeScene::createScene());
}
void Mining::Touch_Building(Ref* pSender)
{
	Savingmanager->Saving();
	Director::getInstance()->replaceScene(BuildingScene::createScene());
}
void Mining::Touch_Shop(Ref* pSender)
{
    Savingmanager->Saving();
    Director::getInstance()->replaceScene(ShoppingScene::createScene());
}

void Mining::Up_Lucky()
{
	if(Defaultmanager::UserLucky<MAX_LUCKYNUM)
    
		m_user->setlucky();
    
}
void Mining::Up_Power(int a)
{
	if(a==1)
    {
		if(Defaultmanager::LaborPower<MAX_POWER)
        {
			labor[0]->setPower();
			Lv[0]->setString(StringUtils::format("Lv%d",Defaultmanager::LaborPower));
		}
	}
    else
    {
		if(Defaultmanager::UserPower<MAX_POWER)
        {
			m_user->setPower();
			Lv[3]->setString(StringUtils::format("Lv%d",Defaultmanager::UserPower));
		}
	}
}
void Mining::Up_Upgrade()
{
	if(Defaultmanager::MinerLevel<MAX_UPGRADENUM)
    {
		Defaultmanager::MinerLevel++;
		Defaultmanager::Reset();
	}
}
void Mining::Up_People()
{
	if(Defaultmanager::LaborNumber<=MAX_PEOPLENUM)
    {
		add_labor(Defaultmanager::LaborNumber);
		labor_on[Defaultmanager::LaborNumber]=true;
		Defaultmanager::LaborNumber++;
	}
}

void Mining::Label_create()//글자 생성
{
	for(int i=0;i<5;i++)
    {
		Lv[i]=Label::createWithTTF("Lv1",FONT,15);
		Lv[i]->setPosition(100,45+i*65);
        Mine->addChild(Lv[i],2);
        
        WantMoney[i]=Label::createWithTTF("0",FONT,15);
        WantMoney[i]->setAnchorPoint(Point(0,0.5));
        WantMoney[i]->setPosition(240,50+i*65);
        Mine->addChild(WantMoney[i],3);
        
        auto coin = Sprite::create("UI/coin.png");
        coin->setScale(0.4);
        coin->setPosition(230,50+i*65);
        Mine->addChild(coin,3);
	}

	Lv[4]->setString(StringUtils::format("Lv%d",Defaultmanager::UserLucky));
	Lv[3]->setString(StringUtils::format("Lv%d",Defaultmanager::UserPower));
	Lv[2]->setString(StringUtils::format("Lv%d",Defaultmanager::MinerLevel));
	Lv[1]->setString(StringUtils::format("Lv%d",Defaultmanager::LaborNumber+1));
	Lv[0]->setString(StringUtils::format("Lv%d",Defaultmanager::LaborPower));
    
    WantMoney[4]->setString(StringUtils::format("%d",Defaultmanager::UserLucky*5000));
    WantMoney[3]->setString(StringUtils::format("%d",Defaultmanager::UserPower*1000));
    WantMoney[2]->setString(StringUtils::format("%d",Defaultmanager::MinerLevel*5000+Defaultmanager::MinerLevel*Defaultmanager::MinerLevel*500));
    WantMoney[1]->setString(StringUtils::format("%d",Defaultmanager::LaborNumber*20000+20000));
    WantMoney[0]->setString(StringUtils::format("%d",Defaultmanager::LaborPower*2000));
}

void Mining::Menu_create()
{
    auto Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Shop=Sprite::create("UI/ShopIcon.png");
	auto Book=Sprite::create("UI/Book.png");
	auto t_Book=Sprite::create("UI/Book.png");
	auto Upgrade=Sprite::create("UI/Upgrade.png");
	auto t_Upgrade=Sprite::create("UI/Upgrade.png");
	auto Building=Sprite::create("UI/Building.png");
	auto t_Building=Sprite::create("UI/Building.png");
    
	t_Book->setOpacity(150);
	t_Upgrade->setOpacity(150);
	t_Building->setOpacity(150);
    t_Shop->setOpacity(150);
    
	auto _ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(Mining::Touch_book,this));
	auto _ui2=MenuItemSprite::create(Upgrade,t_Upgrade,Upgrade,CC_CALLBACK_1(Mining::Touch_Upgrade,this));
	auto _ui3=MenuItemSprite::create(Building,t_Building,Building,CC_CALLBACK_1(Mining::Touch_Building,this));
    auto _ui4=MenuItemSprite::create(Shop, t_Shop,Shop,CC_CALLBACK_1(Mining::Touch_Shop, this));
	auto UI=Menu::create(_ui4,_ui3,_ui1,_ui2,NULL);
    
	UI->alignItemsHorizontallyWithPadding(5);
	UI->setPosition(233,458);

	this->addChild(UI,ui);
}

void Mining::Background_create()
{
	Background=Sprite::create("Background/Mining_Back.png");
	Background->setScaleY(0.875f);
	Background->setAnchorPoint(Point(0,0));
	Background->setPosition(0,235);
	this->addChild(Background,mine_background);
}

void Mining::Scroll_create()
{
	auto tmp_layer = LayerColor::create(Color4B(Color3B(118,107,91)));
	tmp_layer->setContentSize(Size(320, 240));
	tmp_layer->setAnchorPoint(Point(0,0));
	this->addChild(tmp_layer,tmp_layers);

	Mine = LayerColor::create(Color4B(Color3B(118,107,91)));
    Mine->setContentSize(Size(320,330));
                         
	Mine_scroll = ScrollView::create(Size(320, 240), Mine);
    Mine_scroll->setDirection(ScrollView::Direction::VERTICAL);
    Mine_scroll->setBounceable(true);
	Mine_scroll->setContentOffset(Vec2(0.0f,-90.0f));
    this->addChild(Mine_scroll,scroll);
}
