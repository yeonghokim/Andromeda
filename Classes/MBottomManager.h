#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

#define SCALE 0.9

class BottomManager
{
private:
	struct Users
    {
		Sprite* Lucky;
		Sprite* Power;
		Sprite* Upgrade;
		Sprite* People;
		Sprite* Power1;
		Sprite* Power2;
		Sprite* Power3;
		Sprite* Power4;
		Sprite* Power5;
		Sprite* Power6;
		Sprite* Power7;

	};
	
	enum BackPosition
    {
		back1=325,
		back2=260,
		back3=195,
		back4=130,
		back5=65,
		backx=320
	};
    
	enum ButtonPosition
    {
		button1=285,
		button2=220,
		button3=155,
		button4=90,
		button5=25,
		buttonx=263
	};

	bool user;

public:
	Users* u_Background,*u_Button;

	Users* Develop_Setting;

	BottomManager();
	
	void Setting();

	void DeveloperSetting();

	void AddSprite(Node* node);

	void DeveloperAddSprite(Node* node);

	void onTouchBegan(Touch* touch,ScrollView* scroll,bool Developer);
};
