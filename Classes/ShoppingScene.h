#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Popup.h"

USING_NS_CC_EXT;
USING_NS_CC;

class ShoppingScene : public Layer
{
private:
    
    Popup* SellComplete;
    Popup* NoMoney;
    
    Sprite* moll;
    
    Label* SellMoney;
private:
    Sprite* uponSprite=nullptr;
    int upPlanet;
    
    Vector<Sprite*> Planets;
    
    Sprite* BuyButton;
    
    ScrollView* scroll;
    
	Sprite* background;
    
    Texture2D* animation[3];
    
    void ChangeImage(float dt);
    int animate_stack;

public:

    void Touch_book(Ref* pSender);
    
    
    void Touch_Setup(Ref* pSender);
    
    
    void Touch_Building(Ref* pSender);
    
    void Touch_Mine(Ref* pSender);
    
    ShoppingScene();
	~ShoppingScene();
    static  Scene* createScene();
    

    virtual bool init();
    
    CREATE_FUNC(ShoppingScene);
	
	
	EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch,  Event* event);
    
    void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event );
};
