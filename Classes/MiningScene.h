#ifndef __MINING_SCENE_H__
#define __MINING_SCENE_H__

#include "cocos2d.h"
#include "User.h"
#include "Labor.h"
#include "cocos-ext.h"
#include "UpgradeManager.h"
#include "Defaultmanager.h"
#include "MBottomManager.h"
#include "TouchAnimation.h"
#include "Popup.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_POWERNUM 19
#define MAX_LUCKYNUM 14
#define MAX_PEOPLENUM 7
#define MAX_UPGRADENUM 10

#define DEVELOPER false
#define FONT "fonts/arial.ttf"

class Mining : public Layer
{
private:
    Popup* mNoMoney;
    
    TAnimation* _touchAni;
    
    Label* Lv[11];
    
    Label* WantMoney[11];
    
    Label* mMoneyLabel;
    
    Sprite* HealthBar;
    Label* MineHealths;
    
    BottomManager* B_manager;
    
    
    
    EventListenerTouchOneByOne* listener;
public:
    
    static Defaultmanager* Savingmanager;
	enum
    {
		mine_background=0,
		tmp_layers,
		scroll,
		mine_layer0,
		mine_layer1,
		mine_layer2,
		mine_layer3,
		mine_layer4,
		mine_layer5,
		mine_layer6,
		ui
	};

	static User *m_user;
	Labor *labor[8];
private:
    ScrollView* Mine_scroll;
    
    LayerColor* Mine;

    bool labor_on[8];

	Sprite* Background;
private:
	void Scroll_create();

	void Background_create();

	void Menu_create();

	void Label_create();

public:
    /////////////////////////////////////////////////
    void Up_Lucky();
    
    void Up_Power(int a);
    
    void Up_Upgrade();
    
    void Up_People();
    /////////////////////////////////////////////////
    void SetNewMine();

	void update(float dt);
    
	void add_labor(int number);

	void Touch_book(Ref* pSender);
	
	void Touch_Upgrade(Ref* pSender);
	
	void Touch_Building(Ref* pSender);
	
    void Touch_Shop(Ref* pSender);

	void labor_texture(float dt);

	Mining();

	~Mining();

	bool onTouchBegan(Touch* touch, Event *unused_event);

	void onTouchEnded(Touch* touch, Event *unused_event);

    static Scene* createScene();
	
    virtual bool init();

	void  menuCloseCallback(Ref* sender);

	void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event);


    CREATE_FUNC(Mining);
};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
