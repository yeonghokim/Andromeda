
//
//  LoadingScene.h
//  Andromeda
//
//  Created by 김영호 on 2016. 10. 20..
//
//
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LoadingScene : public Layer {
private:
    Texture2D* texture[6];
    
    Sprite* background;
    
    int step;
    
    ProgressTimer* mProgresstimer;
    
public:
    void ChangeBack(float dt);
    
    void update(float dt);
    
    static Scene* createScene();
    
    virtual bool init();

    CREATE_FUNC(LoadingScene);
};
