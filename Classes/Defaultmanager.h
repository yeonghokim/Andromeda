#pragma once

#include "cocos2d.h"

USING_NS_CC;

//==savingmanager
class Defaultmanager : UserDefault
{
private://Auto Saver API
	std::string savingarr[100];//key 값
	int* numarr[100];//넘버의 포인터값을 받아서 동적변화에 대응
    
    std::string strkey[100];
    std::string* strarr[100];
    
    int coin_string;
	int coin_saver;//지금 얼마나 많은 키값이 있는지

public:
	Defaultmanager();

	void Saving();

	void AddSaver(std::string saver,int* num);
    void AddStringSaver(std::string saver, std::string* str);

	int GetData(std::string dataname);

	static int UserPower;//유저의 힘을 나타냄
	static int UserLucky;//유저의 럭키()
	static int Money;//유저가 가지고 있는 돈을 나타냄
	
	static int Rander;//
	static int MinesHealth;//지금 광물의 체력
	static int MinerLevel;//광산의 레벨
	static int MineMoney;//가치
	static int MaxHealth;//광물의 최대체력
	static int LaborNumber;//1234567 LV
	static int LaborPower;//노동자의 힘

	static void Reset();
	static void SetNewMine()
    {
		MinesHealth=pow(MinerLevel,5)*10;
		MaxHealth=MinesHealth;
	}
    
	bool GetData();
};
