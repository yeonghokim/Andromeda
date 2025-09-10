#pragma once

#include "cocos2d.h"
#include "TextureFactory.h"
#include "Defaultmanager.h"
USING_NS_CC;

#define MAX_LUCKY 14
#define MAX_POWER 50
#define MIN_RANDER 15

//
class Labor{
public:

	Layer* layer_labor;

	bool on;//

	Sprite* m_sprite;//
	
	Point m_point;//

	int number;//

private:
	Texture2D* t_first;//텍스쳐
	Texture2D* t_second;
	Texture2D* t_third;

	bool first;//지금 무슨 텍스쳐인지
	bool second;//
	bool third;//

public:
    void ChangeBool()//텍스쳐 초기설정
    {
        int tmp = RandomHelper::random_int(1,3);
        
        first=false;
        second=false;
        third=false;
        
        switch (tmp)
        {
            case 1:
                first=true;
                break;
            case 2:
                second=true;
                break;
            case 3:
                third=true;
                break;
        }
    }
	void setPower()//힘 올려주기
    {
		if(Defaultmanager::LaborPower>MAX_POWER)			
			Defaultmanager::LaborPower=MAX_POWER;
		else
			Defaultmanager::LaborPower++;
	}

	void setnumber(int a);
	//번호 주기

	void setScale(float scale);
	//default=1

	void setTexture(std::string filepath);
    //텍스쳐 설정

	void Add();
    //번호를 이용해 설정
	
	void texture_update(float delta);
    //텍스쳐 바꾸기
	
	void setPosition(const Vec2 &point);
    //포지션 설정
	
	bool init();
	//init

	void dig();
    //땅파기
};
