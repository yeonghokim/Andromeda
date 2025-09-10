#include "BuildingScene.h"
#include "BuildingScrollScene.h"
#include "MiningScene.h"
#include "TextureFactory.h"
#include "MyBodyParser.h"
#include "ShoppingScene.h"
#include "UpgradeScene.h"

#include "MusicManager.h"

bool IsPlanet=false;

void BuildingScene::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();
}

void BuildingScene::onKeyReleased( EventKeyboard::KeyCode keycode, Event *event )
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        Director::getInstance()->replaceScene(Mining::createScene());
    }
}
void BuildingScene::Touch_book(Ref* pSender)
{
    mUpgrade::SaveThePlanet();
    mUpgrade::SaveInventory();
    if(IsPlanet) return;
    Director::getInstance()->replaceScene(ScrollScene::createScene());
}
void BuildingScene::Touch_Upgrade(Ref* pSender)
{
    mUpgrade::SaveThePlanet();
    mUpgrade::SaveInventory();
    if(IsPlanet) return;
    Director::getInstance()->replaceScene(UpgradeScene::createScene());
}
void BuildingScene::Touch_Mine(Ref* pSender)
{
    mUpgrade::SaveThePlanet();
    mUpgrade::SaveInventory();
    if(IsPlanet) return;
	Director::getInstance()->replaceScene(Mining::createScene());
}
void BuildingScene::Touch_Shop(Ref* pSender)
{
    mUpgrade::SaveThePlanet();
    mUpgrade::SaveInventory();
    if(IsPlanet) return;
    Director::getInstance()->replaceScene(ShoppingScene::createScene());
}

Scene* BuildingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = BuildingScene::create();

    scene->addChild(layer);

    return scene;
}

BuildingScene::BuildingScene()
{
    IsPlanet=false;
    Check=false;
	Poped=false;
	makedOb=0;
	delaynum=0;
	touched=true;
	is=0;
	SavingManager = new Defaultmanager();
    step=0;
}
BuildingScene::~BuildingScene()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    
    delete _world;
	delete SavingManager;
	
	SavingManager=nullptr;
    _world = nullptr;
    

}

void BuildingScene::animation_back(float dt)
{
	if(text==1)
    {
		back->setTexture(background2);
		text=2;
	}
    else if(text==2)
    {
		back->setTexture(background3);
		text=3;
	}
    else if(text==3)
    {
		back->setTexture(background1);
		text=1;
	}
}

bool BuildingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    MusicManager::PlayBuilding();
    
	Menu_create();

	addback();

    /////////////////////////////

    winSize = Director::getInstance()->getWinSize();

    b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

    _world = new b2World(gravity);

    _world->SetAllowSleeping(true);

    _world->SetContinuousPhysics(true);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);

    b2Body *groundBody = _world->CreateBody(&groundBodyDef);

    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;
	
    groundEdge.Set(b2Vec2(-100, -100), b2Vec2(100, -100));
    groundBody->CreateFixture(&boxShapeDef);

    groundEdge.Set(b2Vec2(-100, -100), b2Vec2(-100, 1000 / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);

    groundEdge.Set(b2Vec2(-100, 1000 / PTM_RATIO),
        b2Vec2(100, 1000 / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);

    groundEdge.Set(b2Vec2(100, 1000 / PTM_RATIO),
        b2Vec2(100, -100));
    groundBody->CreateFixture(&boxShapeDef);

	//-----------------------------------------------------------------------------
	listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BuildingScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(BuildingScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(BuildingScene::onTouchEnded,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(BuildingScene::tick));
	this->schedule(schedule_selector(BuildingScene::animation_back),0.5);
	this->schedule(schedule_selector(BuildingScene::setdelay),0.1);

    
    if(mUpgrade::In_Planet.size()>1)
    {
        InPlanet* planet = mUpgrade::In_Planet.at(mUpgrade::In_Planet.size()-2);
        below2_sprite=Sprite::create(StringUtils::format("planet%d/%d.png", planet->GetKind(), planet->GetUpgrade()));
        below2_sprite->setPosition(160,10);
        below2_sprite->setScale(0.8);
        this->addChild(below2_sprite,Zorder::n_sprite);
    }
    else
        below2_sprite=nullptr;

    if(mUpgrade::In_Planet.size()!=0)
    {
        InPlanet* planet = mUpgrade::In_Planet.at(mUpgrade::In_Planet.size()-1);
        below_sprite=Sprite::create(StringUtils::format("planet%d/%d.png", planet->GetKind(), planet->GetUpgrade()));
        below_sprite->setPosition(160,100);
        below_sprite->setScale(0.8);
        this->addChild(below_sprite,Zorder::n_sprite);
    }
    else
        below_sprite=nullptr;

	L_Pop= Layer::create();
	this->addChild(L_Pop,Zorder::_popup);
    
    
    if(mUpgrade::Inventory_Planet.size()!=0){
        mars = Sprite::create(StringUtils::format("planet%d/%d.png"
                                                  , mUpgrade::Inventory_Planet.at(0)->GetKind(),
                                                  mUpgrade::Inventory_Planet.at(0)->GetUpgrade()));
        mars ->setPosition(160,55);
        L_Pop->addChild(mars);
        
        m_count=Label::createWithTTF(StringUtils::format("%d",mUpgrade::Inventory_Planet.at(0)->Getnum()), "fonts/arial.ttf", 30);
        m_count->setColor(Color3B::BLACK);
        m_count->setPosition(110,50);
        L_Pop->addChild(m_count);
    }else{
        Label* label = Label::createWithTTF("No Planet", "fonts/arial.ttf", 20);
        label->setPosition(160,50);
        label->setColor(Color3B::BLACK);
        L_Pop->addChild(label,2);
        step=-1;
    }
    
    left = Sprite::create("UpgradeScene/button.png");
    left->setPosition(80,50);
    L_Pop->addChild(left);
    
    BuildBox=Sprite::create("UI/BuildBox.png");
    BuildBox->setAnchorPoint(Point(0.5,0));
    BuildBox->setPositionX(160);
    L_Pop->addChild(BuildBox,-1);
    
    right = Sprite::create("UpgradeScene/button1.png");
    right->setPosition(250,50);
    L_Pop->addChild(right);

	Add_obtacle(Point(0,250));
    
    this->setKeypadEnabled(true);

	return true;
}
void BuildingScene::Create_obtacle(float dt)
{
	if(makedOb<0)
    {
		Add_obtacle(Point(0,250));
		makedOb++;
	}
}
void BuildingScene::setdelay(float dt)
{
	if(delaynum==0) touched=true;
	if(delaynum!=0) delaynum--;
}
void BuildingScene::tick(float dt)
{
		b2Body* tmp;
		bool on=false;

		b2Body* tmp2;
		bool on2=false;

		int velocityIterations = 8;
		int positionIterations = 3;

		_world->Step(dt, velocityIterations, positionIterations);
		
		b2Body *b;
		for (b= _world->GetBodyList(); b; b = b->GetNext())
		{
			if (b->GetUserData() != nullptr&& b->GetType()==b2_dynamicBody)
            {
				Sprite* spriteData = (Sprite*)b->GetUserData();
				int a=b->GetPosition().x * PTM_RATIO;
				int c=b->GetPosition().y * PTM_RATIO;
				spriteData->setPosition(Point(a,c));
				spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
			if (b->GetUserData() != nullptr&& b->GetType()==b2_kinematicBody)
            {
				Sprite* spriteData = (Sprite*)b->GetUserData();
				if(spriteData!=nullptr)
                {
					spriteData->setPosition(Point(b->GetPosition().x * PTM_RATIO,
						b->GetPosition().y * PTM_RATIO));
					spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
				}
			}
			if(b->GetUserData()!=nullptr&&b->GetType()==b2_dynamicBody)
            {
				int j=b->GetPosition().y*PTM_RATIO;
				int i=b->GetPosition().x*PTM_RATIO;

				if(i!=160)
                {
					tmp2=b;
					on2=true;
				}

				if(j<190&&j!=100&&i==160)
                {
					tmp=b;
					on=true;
				}

			}
			if(b->GetUserData()!=nullptr&&b->GetType()==b2_kinematicBody)
            {
				int i=b->GetPosition().x*PTM_RATIO;
				if(i>winSize.width+50)
                {
					b->SetLinearVelocity(b2Vec2(-10.0f,-2.5f));
				}
                else if(i<-50)
                {
					b->SetLinearVelocity(b2Vec2(10.0f,2.5f));
				}
			}
		}
    
		if(on)
        {
			RandAction(tmp);	
		}
		if(on2)
        {
			ParticleSystemQuad* exp = ParticleSystemQuad::create("Particle/particle.plist");
			exp->setPosition(tmp2->GetPosition().x*PTM_RATIO,tmp2->GetPosition().y*PTM_RATIO);
			exp->setScale(0.5);
			this->addChild(exp);
		
			tmp2->DestroyFixture(tmp2->GetFixtureList());

			tmp2->SetUserData(nullptr);
		
			this->removeChild(body_sprite);
            
            body_sprite=NULL;
		
			tmp2=nullptr;
            IsPlanet=false;
		}	
	
}

bool BuildingScene::onTouchBegan(Touch* touch, Event* event)
{
    if(Poped){
        Rect Right=right->getBoundingBox();
        Rect Left=left->getBoundingBox();
        Right = Rect(Right.getMinX(),Right.getMinY()+280,Right.getMaxX()-Right.getMinX(),Right.getMaxY()-Right.getMinY());
        Left = Rect(Left.getMinX(),Left.getMinY()+280,Left.getMaxX()-Left.getMinX(),Left.getMaxY()-Left.getMinY());
        if(Left.containsPoint(touch->getLocation())){
            left->setOpacity(200);
        }else if(Right.containsPoint(touch->getLocation())){
            right->setOpacity(200);
        }
    }

    return true;
}
void BuildingScene::onTouchMoved(Touch* touch, Event* event)
{
	

}
void BuildingScene::onTouchEnded(Touch* touch, Event* event)
{
	
    Point point=touch->getLocation();
    
    Rect Right=right->getBoundingBox();
    Rect Left=left->getBoundingBox();
    
    left->setOpacity(255);
    right->setOpacity(255);

    if(BuildBox->getBoundingBox().containsPoint(point)){
        if(step!=(-1)){
            Rect r_Planet = mars->getBoundingBox();
            if(r_Planet.containsPoint(touch->getLocation())){
                Planet* planet =mUpgrade::Inventory_Planet.at(step);
                SelectedPlanet= new InPlanet(planet->GetKind(),planet->GetUpgrade());
                set_nexttexture(planet->GetUpgrade(), planet->GetKind());
                if(!Check)
                {
                    above_sprite=Sprite::createWithTexture(next_texture);
                    above_sprite->setPosition(160,400);
                    above_sprite->setScale(0.8);
                    this->addChild(above_sprite);
                    Check=true;
                }
                else
                {
                    above_sprite->setTexture(next_texture);
                }
            }
        }
        if(Left.containsPoint(touch->getLocation())){
            LeftB();
            
        }else if(Right.containsPoint(touch->getLocation())){
            RightB();
            
        }
        return;
    }
	
	if(!UI->getBoundingBox().containsPoint(touch->getLocation())&&touched&&Check)
    {
        mUpgrade::Inventory_Planet.at(step)->minusPlanet();
        if(mUpgrade::Inventory_Planet.at(step)->Getnum()==0){
            mUpgrade::Inventory_Planet.erase(mUpgrade::Inventory_Planet.begin()+step);
        }
        if(mUpgrade::Inventory_Planet.size()==0){
            Label* label = Label::createWithTTF("No Planet", "fonts/arial.ttf", 20);
            label->setPosition(160,50);
            label->setColor(Color3B::BLACK);
            L_Pop->addChild(label,2);
            m_count->setVisible(false);
            mars->setVisible(false);
            step=-1;
        }else if(step>=mUpgrade::Inventory_Planet.size()){
            Planet* planet = mUpgrade::Inventory_Planet.at(mUpgrade::Inventory_Planet.size()-1);
            auto spr = Sprite::create(StringUtils::format("planet%d/%d.png", planet->GetKind(),planet->GetUpgrade()));
            mars->setTexture(spr->getTexture());
            m_count->setString(StringUtils::format("%d",planet->Getnum()));
            step=mUpgrade::Inventory_Planet.size()-1;
        }
        else{
            mars->setTexture(StringUtils::format("planet%d/%d.png", mUpgrade::Inventory_Planet.at(step)->GetKind(),mUpgrade::Inventory_Planet.at(step)->GetUpgrade()));
            m_count->setString(StringUtils::format("%d",mUpgrade::Inventory_Planet.at(step)->Getnum()));
        }
        
        IsPlanet=true;
		addNewSpriteAtPosition(Point(160,400));
		Check=false;
		above_sprite->setVisible(false);
		this->removeChild(above_sprite);
		above_sprite=nullptr;
		touched=false;
		delaynum+=10;
        

	}

}

void BuildingScene::addNewSpriteAtPosition(Vec2 location)
{
	Sprite* pSprite = Sprite::createWithTexture(above_sprite->getTexture());
	
	//this->removeChild(above_sprite);
	//above_sprite=nullptr;
	
    pSprite->setPosition(Vec2(location.x, location.y));
	pSprite->setScale(0.8);
	this->addChild(pSprite,Zorder::n_sprite);
	
	body_sprite=pSprite;

	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	bodyDef.userData = pSprite;

    b2Body* body = _world->CreateBody(&bodyDef);
    
	b2CircleShape circle;
    circle.m_radius =BODY_RADIO;

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = restitutions;

    body->CreateFixture(&fixtureDef);
}
void BuildingScene::Add_obtacle(Vec2 location)
{
    float slopex=13.0f+RandomHelper::random_int(0, 1);
    
	Sprite* pSprite = Sprite::create("Obstacle/Obstacle1.png");
    pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);
	body_sprite=pSprite;

	b2BodyDef bodyDef;

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO); 
	bodyDef.linearVelocity = b2Vec2(slopex,slopex/4);

	bodyDef.userData = pSprite;

    b2Body* body = _world->CreateBody(&bodyDef);

	MyBodyParser::getInstance()->parseJsonFile("Obstacle/Obstacle1.json");
	MyBodyParser::getInstance()->b2BodyJson(pSprite,"Obstacle2",body);

}

void BuildingScene::addback()
{
	background1=TextureFactory::Create("Background/background2_1.png");
	background2=TextureFactory::Create("Background/background2_2.png");
	background3=TextureFactory::Create("Background/background2_3.png");

	back=Sprite::createWithTexture(background1);
	back->setAnchorPoint(Point(0,0));
    this->addChild(back,Zorder::n_background);
	text=1;
}

void BuildingScene::Menu_create()
{
    auto Shop=Sprite::create("UI/ShopIcon.png");
    auto t_Shop=Sprite::create("UI/ShopIcon.png");
	auto t_Book=Sprite::create("UI/Book.png");
	auto t_Upgrade=Sprite::create("UI/Upgrade.png");
	auto t_Mine=Sprite::create("UI/Mining.png");
	auto Mine=Sprite::create("UI/Mining.png");
	auto Upgrade=Sprite::create("UI/Upgrade.png");
	auto Book=Sprite::create("UI/Book.png");
    t_Shop->setOpacity(150);
	t_Book->setOpacity(150);
	t_Upgrade->setOpacity(150);
	t_Mine->setOpacity(150);

    auto _ui1=MenuItemSprite::create(Book,t_Book,Book,CC_CALLBACK_1(BuildingScene::Touch_book,this));
	auto _ui2=MenuItemSprite::create(Upgrade,t_Upgrade,Upgrade,CC_CALLBACK_1(BuildingScene::Touch_Upgrade,this));
	auto _ui3=MenuItemSprite::create(Mine,t_Mine,Mine,CC_CALLBACK_1(BuildingScene::Touch_Mine,this));
    auto _ui4=MenuItemSprite::create(Shop, t_Shop,Shop,CC_CALLBACK_1(BuildingScene::Touch_Shop, this));

	UI=Menu::create(_ui4,_ui3,_ui1,_ui2,NULL);
	UI->alignItemsHorizontallyWithPadding(5);
	UI->setPosition(233,458);

	this->addChild(UI,100);
}
void BuildingScene::set_nexttexture(int Upgrade, int Kind)
{
	//previous_texture
	//next_texture
    next_texture=Sprite::create(StringUtils::format("planet%d/%d.png",Kind,Upgrade))->getTexture();
}

void BuildingScene::RandAction(b2Body* b)
{
	if(b->GetType()==b2_kinematicBody) return;

    if(RandomHelper::random_int(0, 99)<LUCKY_PERCENT)
    {
		b->DestroyFixture(b->GetFixtureList());
		//_world->DestroyBody(b);
		b->SetUserData(nullptr);
		action_sprite=Sprite::createWithTexture(body_sprite->getTexture());
		
		this->removeChild(body_sprite);
		body_sprite=nullptr;		
		b=nullptr;
		action_sprite->setPosition(160,190);
		action_sprite->setScale(0.8);
		this->addChild(action_sprite);
		action_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));
        
		if(below_sprite!=nullptr)
			below_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));
		if(below2_sprite!=nullptr)
			below2_sprite->runAction(MoveBy::create(1.0,Point(0,-90)));

		below2_sprite=below_sprite;
		
		below_sprite=action_sprite;
    
        mUpgrade::In_Planet.push_back(SelectedPlanet);
        mUpgrade::SaveThePlanet();
        mUpgrade::SaveInventory();
        
        
        
        
		delaynum+=10;
	}
    else
    {
		b->DestroyFixture(b->GetFixtureList());

		b->SetUserData(nullptr);
		
		this->removeChild(body_sprite);
		
		b=nullptr;
	}
    
    IsPlanet=false;
    
	SavingManager->Saving();
}
Rect BuildingScene::UpRect(Rect rect, int y)
{
	return rect=Rect(rect.getMinX(),rect.getMinY()+y,80,80);
}
void BuildingScene::PlanetChange()
{
    Planet* planet = mUpgrade::Inventory_Planet.at(step);
    auto spr = Sprite::create(StringUtils::format("planet%d/%d.png", planet->GetKind(),planet->GetUpgrade()));
    mars->setTexture(spr->getTexture());
    m_count->setString(StringUtils::format("%d",planet->Getnum()));
}

void BuildingScene::RightB()
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
void BuildingScene::LeftB()
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
