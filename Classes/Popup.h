#pragma once

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class Popup
{
private:
    std::string mString;
    
    Layer* mLayer;

    Sprite* mPopup;
    Sprite* mOkayButton;
    
    Label* mLabel;
public:
    
    void SetString(std::string str){mString=str;}
    
    Layer* GetLayer(){return mLayer;}
    
    Popup();
	~Popup();

	void Init();
	
	Layer* on();
	void off();

	bool OnThis;

	void RemoveThis();

	bool onTouchBegan(Touch *touch);
	void onTouchMoved(Touch *touch);
	void onTouchEnded(Touch *touch);
 

};

