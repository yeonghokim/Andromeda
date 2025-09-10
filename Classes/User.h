#pragma once

#include"cocos2d.h"
#include "Defaultmanager.h"
USING_NS_CC;

#define MAX_LUCKY 14
#define MAX_POWER 50
#define MIN_RANDER 15

#define MoneyType int

class User{
public:
#pragma region FEATURE
	Sprite* main;
	Label* mine;
#pragma endregion
    
    MoneyType* Money;
	
public:
    User(int* pMoney):Money(pMoney){}
    
    bool MinusMoney(int price){
        if(*Money>=price){
           *Money-=price;
            return true;
            CCLOG("%d was priced",price);
        }else return false;
        
        
    }
    
	void setPower(){
		if(Defaultmanager::UserPower>MAX_POWER)
			Defaultmanager::UserPower=MAX_POWER;
		else
			Defaultmanager::UserPower++;
	}
	
	void setlucky(){
		if(Defaultmanager::UserLucky>MAX_LUCKY) 
			Defaultmanager::UserLucky= MAX_LUCKY;
		else
			Defaultmanager::UserLucky++;	
	}

	void Touched(Touch* touch);
	
	void dig();
};
