#pragma once

#include"cocos2d.h"

USING_NS_CC;

class Back
{
private:
	bool Visible;

	Sprite* Main;

	Sprite* Okay;

	Sprite* Cancel;

	Layer* _layer;

public:
	Back();

	void On();

	void onTouchBegan(Touch* touch);

	int onTouchEnded(Touch* touch);

	Layer* Getlayer();
};
