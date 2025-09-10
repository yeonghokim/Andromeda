//
//  SellManager.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 11. 3..
//
//

#include "SellManager.h"
#include "UpgradeManager.h"

int SellManager::Calculate(){
    int sum=0;
    int step=0;
    for(InPlanet* planet : mUpgrade::In_Planet){
        
        int k =planet->GetKind();
        
        int General = k*800+(k-1+RandomHelper::random_int(0, 2))*300*k;
        
        if(k>6)
            General*=(k-6);
        
        sum+=General*1.5;
        
    }
    return sum;
}
