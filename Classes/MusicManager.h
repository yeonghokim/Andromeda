//
//  MusicManager.h
//  Andromeda
//
//  Created by 김영호 on 2016. 11. 15..
//
//
#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class MusicManager{
public:
    static void PlayBuilding();
    static void PlayClear();
    static void PlayMenu();
    static void PlayMining();
    static void PlayShopping();
    static void PlayUpgrade();
};
