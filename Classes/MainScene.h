//
//  MainScene.h
//  Andromeda
//
//  Created by 김영호 on 2016. 11. 10..
//
//
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MainScene : public Layer{
private:
    int mTouchNumber;
    
    Sprite* mBackground;
    
    Sprite* mMainRect;
    Sprite* mLeft;
    Sprite* mRight;
    
    Label* mLabel;
    
public:
    void onKeyReleased( EventKeyboard::KeyCode keycode, Event *event );
    bool onTouchBegan(Touch* touch, Event* unused_event);
    void onTouchEnded(Touch* touch, Event* unused_event);
            
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MainScene);
};
