#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Defaultmanager.h"
#include "Backmanager.h"
#include "UpgradeManager.h"

#define PTM_RATIO 32

#define BODY_RADIO 1.1

#define restitutions 0.3f
			
#define LUCKY_PERCENT 100

USING_NS_CC;

class BuildingScene : public Layer
{
public:
	void setdelay(float dt);

	void Create_obtacle(float dt);
	
	void RandAction(b2Body* b);

	void animation_back(float dt);

	void tick(float dt);

	void Touch_book(Ref* pSender);
	
	void Touch_Upgrade(Ref* pSender);
	
	void Touch_Mine(Ref* pSender);
    
    void Touch_Shop(Ref* pSender);

	void addback();

	void Menu_create();

	void addNewSpriteAtPosition( Vec2 location);

	void Add_obtacle(Vec2 location);

	void set_nexttexture(int Upgrade, int Kind);

	void  menuCloseCallback(Ref* sender);

	void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event);
    
public:
    Menu* UI;
    
	Sprite* above_sprite;
	Sprite* body_sprite;

	int is;
	Sprite* below2_sprite;
	Sprite* below_sprite;
	Sprite *action_sprite;

	bool touched;
public:
    
	Layer* L_Pop;
	
	bool Poped;

    Sprite *background;
    Sprite *mars;
    Label* m_count;
    
    Sprite* BuildBox;
    Sprite *left;
    Sprite *right;
    
    void PlanetChange();
    
    int step;
    
    void RightB();
    void LeftB();

	Rect UpRect(Rect rect, int y);

public:

    int makedOb;

	enum Zorder
    {
		n_background=0,
		n_sprite=1,
		_layers=2,
		_popup=3
	};

    static  Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(BuildingScene);
	
	BuildingScene();    
	~BuildingScene();
	
	EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
    
private:
    //Saving
    
    InPlanet* SelectedPlanet;
    
public:
	int delaynum;
    
	bool Check;

	Defaultmanager* SavingManager;

	Size winSize;

    b2World* _world;
	
	Sprite* back;

	int text;

	Texture2D* background1;
	Texture2D* background2;
	Texture2D* background3;
	
	Texture2D* previous_texture;
    Texture2D* previous2_texture;

	Texture2D* next_texture;

};
