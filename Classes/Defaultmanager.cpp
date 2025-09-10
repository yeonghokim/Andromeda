#include "Defaultmanager.h"

int Defaultmanager::UserPower=1;
int Defaultmanager::UserLucky=1;
int Defaultmanager::Money=0;
int Defaultmanager::Rander=60;
int Defaultmanager::MinesHealth=50;
int Defaultmanager::MinerLevel=1;
int Defaultmanager::LaborNumber=0;
int Defaultmanager::LaborPower=1;
int Defaultmanager::MineMoney=0;
int Defaultmanager::MaxHealth=0;
//-------------------------------this is unchangable-----------------------------------------------//
void Defaultmanager::Saving()
{
	for(int i=0;i<coin_saver;i++)
		setIntegerForKey(savingarr[i].c_str(),*numarr[i]);
    for(int i=0;i<coin_string;i++)
        setStringForKey(strkey[i].c_str(), *strarr[i]);
}

Defaultmanager::Defaultmanager()
{

	coin_saver=0;
    coin_string=0;
}

void Defaultmanager::AddSaver(std::string saver,int* num)
{
	savingarr[coin_saver]=saver;
	numarr[coin_saver]=num;
    
	coin_saver++;
}
void Defaultmanager::AddStringSaver(std::string saver, std::string* str){
    strkey[coin_string]=saver;
    strarr[coin_string]=str;
    
    coin_string++;
}


int Defaultmanager::GetData(std::string dataname)
{
	return getIntegerForKey(dataname.c_str());
}
bool Defaultmanager::GetData()
{
    //값 받아오기
	UserPower=GetData("User_power");
	UserLucky=GetData("User_lucky");
	MinerLevel= GetData("MineUpgrade");
	LaborNumber= GetData("Labornum");
	LaborPower= GetData("LaborPower");
    Money = GetData("Money");
    MineMoney = GetData("MineMoney");
    
	if(MaxHealth==0)//처음 들어올때 Reset();
        Reset();
	return true;
}
void Defaultmanager::Reset()//눌러질때마다 마인의 체력이 달라짐
{
	MinesHealth=pow(MinerLevel,5)*10;
	MaxHealth=MinesHealth;
	Rander=100-(MinerLevel+1)*5-30;
}
