//
//  Planet.h
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 8..
//
//
#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define MAX_UPGRADE 10



class Planet : public Ref{
protected:
    int Upgrade;
    
    int person;
    
    int Kind;
    
    int number;
    
public:
    int GetUpgrade(){return Upgrade;}
    
    int GetKind(){return Kind;}
    
    int Getnum(){return number;}
    
    void addPlanet(){
        number++;
    }
    
    void minusPlanet(){
        number--;
        return;
    }
    
    void UpgradePlanet(){
        if(Upgrade<5)
            Upgrade++;
    }
    
    Planet():person(0),Upgrade(1),Kind(0){
    
    }
    Planet(int kind, int upgrade, int number):person(0),Upgrade(upgrade),Kind(kind),number(number){
        
    }
};
class InPlanet : public Ref{
protected:
    int Upgrade;
    
    int person;
    
    int Kind;
    
public:
    int GetUpgrade(){return Upgrade;}
    
    int GetKind(){return Kind;}
    
    InPlanet():person(0),Upgrade(1),Kind(0){
        
    }
    InPlanet(int kind, int upgrade):person(0),Upgrade(upgrade),Kind(kind){
        
    }
    
    
};
