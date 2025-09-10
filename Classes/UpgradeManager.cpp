//
//  UpgradeManager.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 9. 26..
//
//
#include "UpgradeManager.h"

std::vector<Planet*> mUpgrade::Inventory_Planet;//지금 가지고 있는 행성
std::vector<InPlanet*> mUpgrade::In_Planet;

void mUpgrade::SaveThePlanet()
{
    int PlanetNum =(int)In_Planet.size();
    
    std::string saveData=StringUtils::format("InUpgrade%4d{",PlanetNum);
    
    int step=0;
    
    for(InPlanet* planet : In_Planet){
        std::string save = StringUtils::format("%2d:%4d:%d,",planet->GetKind(),step++,planet->GetUpgrade());
        saveData+=save;
    }
    if(PlanetNum!=0)
    saveData.erase(saveData.size()-1);
    saveData+="}";
    
    UserDefault::getInstance()->setStringForKey("InUpgrade", saveData);
    GetThePlanet();
}
void mUpgrade::GetThePlanet()
{//쌓아져 있는 행성들 데이터
    
    std::vector<InPlanet*> tmp;
    std::string saveData= UserDefault::getInstance()->getStringForKey("InUpgrade");
    
    std::string intData="";
    intData+=saveData.at(9);
    intData+=saveData.at(10);
    intData+=saveData.at(11);
    intData+=saveData.at(12);
    
    int PlanetNum=std::atoi(intData.c_str());
    std::string str="";
    for(int i=0;i<PlanetNum;i++){
        str+=saveData.at(14+i*10);
        str+=saveData.at(15+i*10);
        int kind= std::atoi(str.c_str());
        
        int UpgradeNum = std::atoi(&saveData.at(22+i*10));
        
        auto planet= new InPlanet(kind,UpgradeNum);
        
        tmp.push_back(planet);
        
        str="";
    }
    In_Planet=tmp;
}
void mUpgrade::SaveInventory()
{
    std::vector<Planet*> tmp;
    for(Planet* planet : Inventory_Planet){
        if(planet->Getnum()!=0){
            tmp.push_back(planet);
        }
    }
    
    int PlanetNum =(int)tmp.size();
    
    std::string saveData=StringUtils::format("UpgradeData%4d{",PlanetNum);
    
    int PlanetData[11][11]={0};
    
    for(Planet* planet : tmp){
        std::string save = StringUtils::format("%2d:%d:%4d,",planet->GetKind(),planet->GetUpgrade(),planet->Getnum());
        saveData+=save;
    }
    if(PlanetNum!=0)
    saveData.erase(saveData.size()-1);
    saveData+="}";
    
    UserDefault::getInstance()->setStringForKey("UpgradeData", saveData);
    GetInventory();
    
}
void mUpgrade::GetInventory()
{//인벤토리에 있는 행성들 데이터
    std::vector<Planet*> tmp;
    std::string saveData= UserDefault::getInstance()->getStringForKey("UpgradeData");
    
    std::string intData="";
    intData+=saveData.at(11);
    intData+=saveData.at(12);
    intData+=saveData.at(13);
    intData+=saveData.at(14);
    
    int PlanetNum=std::atoi(intData.c_str());

    std::string str="";
    for(int i=0;i<PlanetNum;i++)
    {//{123:123:123}
        str+=saveData.at(16+i*10);
        str+=saveData.at(17+i*10);
        int kind = std::atoi(str.c_str());
        str="";
        
        int upgrade = std::atoi(&saveData.at(19+i*10));
        str+=saveData.at(21+i*10);
        str+=saveData.at(22+i*10);
        str+=saveData.at(23+i*10);
        str+=saveData.at(24+i*10);
        
        int num = std::atoi(str.c_str());
        
        auto planet= new Planet(kind,upgrade,num);
        
        tmp.push_back(planet);
        str="";
    }
    Inventory_Planet=tmp;
}
