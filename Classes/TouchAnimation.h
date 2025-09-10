//
//  TouchAnimation.h
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 22..
//
//
#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define MoveValue 30.0f

class TAnimation{
private:
    
    Layer* Parents;
    
    Texture2D* Rock[3];
    
    Touch* touch;
    
public:
    
    TAnimation(){
        
    }
    
    void InitTexture();
    
    void SetLayer(Layer* layer);
    
    void TouchAnimation(Touch* touch);
    
};
