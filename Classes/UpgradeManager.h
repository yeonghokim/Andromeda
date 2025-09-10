//
//  UpgradeManager.h
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 26..
//
//

#pragma  once

#include "cocos2d.h"
#include "Planet.h"

USING_NS_CC;

class mUpgrade{
public:
    static std::vector<Planet*> Inventory_Planet;//지금 가지고 있는 행성   @ @
    static std::vector<InPlanet*> In_Planet;//지금 쌓아져 있는 행성
    
    static void SaveThePlanet();//I_Planet
    
    static void GetThePlanet();//I_Planet
    
    static void SaveInventory();
    static void GetInventory();
    
    void upgradePlanet(int step){
        Planet* planet = Inventory_Planet.at(step);
        int kind = planet->GetKind();
        int upgrade = planet ->GetUpgrade();
        
        bool tmp =true;
        for(Planet* ifplanet :Inventory_Planet){
            if(ifplanet->GetKind()==kind&&ifplanet->GetUpgrade()==upgrade+1){
                ifplanet->addPlanet();
                tmp=false;
            }
        }
        if(tmp){
            Planet* newplanet = new Planet(planet->GetKind(),planet->GetUpgrade()+1,1);
            Inventory_Planet.push_back(newplanet);
        }
        
        planet->minusPlanet();
        
        SaveInventory();
        
        
    }
};
