//
//  TouchAnimation.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 22..
//
//
#include "TouchAnimation.h"

void TAnimation::InitTexture()
{
    for(int i=0;i<3;i++)
    {
        Image* image = new Image();
        image->initWithImageFile(StringUtils::format("Touch/Texture%d.png",i+1));
        
        Texture2D* texture =new Texture2D();
        texture->initWithImage(image);
        
        Rock[i]=texture;
    }
    
}
void TAnimation::TouchAnimation(cocos2d::Touch *touch)
{
    this->touch=touch;
    
    Point position = touch->getLocation();// 터치 위치
    
    int type= RandomHelper::random_int(1, 4);//Integer 값
    
    float Theta=RandomHelper::random_real(0.0f, 2.0f);//float 값
    
    Vec2 action[3];
    
    action[0] = Vec2(  cos(Theta*M_PI)*MoveValue,  sin(Theta*M_PI)*MoveValue  );//라디안 값 넣어주기
    
    action[1] = Vec2(  cos((Theta+2/(float)3)*M_PI)*MoveValue,  sin((Theta+2/(float)3)*M_PI)*MoveValue  );//라디안 값 넣어주기
    
    action[2] = Vec2(  cos((Theta+4/(float)3)*M_PI)*MoveValue,  sin((Theta+4/(float)3)*M_PI)*MoveValue  );//라디안 값 넣어주기
    
    for(int i=0;i<3;i++)
    {
        
        auto spr = Sprite::createWithTexture(Rock[i]);
        
        spr->setPosition(position);
        
        FadeOut* fadeout = FadeOut::create(0.3);
        
        MoveBy* move = MoveBy::create(0.3, action[i]);
        
        RotateBy* rotate=RotateBy::create(0.3, RandomHelper::random_int(360, 1080));
        
        Spawn* spawn =Spawn::create(fadeout,move,rotate, NULL);
        
        Parents->addChild(spr,100000);
        
        spr->runAction(spawn);
        
    }
    
}
void TAnimation::SetLayer(Layer *layer)
{
    Parents=layer;
}
