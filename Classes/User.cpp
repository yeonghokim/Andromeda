#include "User.h"

void User::Touched(Touch* touch){
		dig();
}

void User::dig(){
	
	int *a=&Defaultmanager::MinesHealth;

	*a-=pow(Defaultmanager::UserPower,2);
}

