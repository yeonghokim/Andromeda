//
//  MusicManager.cpp
//  Andromeda
//
//  Created by 김영호 on 2016. 11. 15..
//
//
#include "MusicManager.h"
void MusicManager::PlayBuilding(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/BuildingMusic.wav",true);
}
void MusicManager::PlayClear(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/ClearMusic.wav",true);
}
void MusicManager::PlayMenu(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MenuMusic.wav",true);
}
void MusicManager::PlayMining(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/MiningMusic.mp3",true);
}
void MusicManager::PlayShopping(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/ShoppingMusic.mp3",true);
}
void MusicManager::PlayUpgrade(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/UpgradeMusic.wav",true);
}
