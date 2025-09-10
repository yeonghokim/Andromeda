#pragma once

#include"cocos2d.h"

USING_NS_CC;

//Texture
class TextureFactory
{
public:
	static Texture2D* Create(std::string filepath);
};
