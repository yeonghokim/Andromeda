#pragma once

#include "cocos2d.h"
#include "TextureFactory.h"
#include "cocos-ext.h"
#include "PopUp.h"
USING_NS_CC_EXT;
USING_NS_CC;	

class ScrollScene : public Layer
{
private:
    Popup* Complete;
    
    int sell;
    
    Label* sellMoney;
    
    Sprite* sellButton;
    
private://Saving + Texture
	Vector<Sprite*> drawed;

    std::string BuiltsData;
    
    int makednumber;

    bool EndDraw;//그리는게 끝났는지?
    
private://Layer
	ScrollView* scroll;//ScrollView
	
	Layer* Built;//Scroll Layer
    
private://Background
    Sprite* Background[30];//10개의 그림을 붙여서 긴 그림을 만듬
    
	int number;//지금 백그라운드 상태

    Texture2D* one;
    Texture2D* two;
    Texture2D* three;
    
public://cocos API
    static  Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(ScrollScene);

    virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchEnded( Touch *touch,  Event* unused_event);
    
public://Method
    void SpriteCr(int count);
    
    void Change(int Upgrade, int Kind, int x, int y);
    
	void ChangeBack(float dt);

	void  Menu_create();

	void drawdt(float dt);

	void drawTexture(int number);

	void create_b()
    {
		for(int i=0;i<30;i++)
        {
			Background[i]=Sprite::createWithTexture(i%3==0?one:i%3==1?two:three);
			Background[i]->setAnchorPoint(Point(0,0));
			Background[i]->setPosition(0,i*480);
			Built->addChild(Background[i],0);
		}
		number=1;
	}

	void Touch_building(Ref* pSender);

	void Touch_Setup(Ref* pSender);

	void Touch_Mine(Ref* pSender);
    
    void Touch_Shop(Ref* pSender);
    
    void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event);
};

