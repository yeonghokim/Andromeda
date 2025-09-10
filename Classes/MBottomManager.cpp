#include "MBottomManager.h"

BottomManager::BottomManager()
{
	u_Background=new Users;
	u_Button = new Users;
	Develop_Setting = new Users;
	user=true;
}
void BottomManager::Setting()
{
	u_Background->Lucky=Sprite::create("UI/b_lucky.png");
	u_Background->Lucky->setScaleY(SCALE);
    u_Background->Lucky->setPosition(BackPosition::backx,BackPosition::back1);
	u_Background->Lucky->setAnchorPoint(Point(1,1));

	u_Background->Power=Sprite::create("UI/b_power.png");
	u_Background->Power->setScaleY(SCALE);
	u_Background->Power->setPosition(BackPosition::backx,BackPosition::back2);
	u_Background->Power->setAnchorPoint(Point(1,1));

	u_Background->Upgrade=Sprite::create("UI/b_upgrade.png");
	u_Background->Upgrade->setScaleY(SCALE);
	u_Background->Upgrade->setPosition(BackPosition::backx,BackPosition::back3);
	u_Background->Upgrade->setAnchorPoint(Point(1,1));
    
	u_Background->People=Sprite::create("UI/b_people.png");
	u_Background->People->setScaleY(SCALE);
	u_Background->People->setPosition(BackPosition::backx,BackPosition::back4);
	u_Background->People->setAnchorPoint(Point(1,1));

	u_Background->Power1=Sprite::create("UI/b_laborpower.png");
	u_Background->Power1->setScaleY(SCALE);
	u_Background->Power1->setPosition(BackPosition::backx,BackPosition::back5);
	u_Background->Power1->setAnchorPoint(Point(1,1));

	////////////////////////////////////////////////////
	u_Button->Lucky=Sprite::create("UI/button.png");
	u_Button->Lucky->setScale(SCALE);
    u_Button->Lucky->setPosition(ButtonPosition::buttonx,ButtonPosition::button1);
		
	u_Button->Power=Sprite::create("UI/button.png");
	u_Button->Power->setScale(SCALE);
	u_Button->Power->setPosition(ButtonPosition::buttonx,ButtonPosition::button2);
		
	u_Button->Upgrade=Sprite::create("UI/button.png");
	u_Button->Upgrade->setScale(SCALE);
	u_Button->Upgrade->setPosition(ButtonPosition::buttonx,ButtonPosition::button3);

	u_Button->People=Sprite::create("UI/button.png");
	u_Button->People->setScale(SCALE);
	u_Button->People->setPosition(ButtonPosition::buttonx,ButtonPosition::button4);

	u_Button->Power1=Sprite::create("UI/button.png");
	u_Button->Power1->setScale(SCALE);
	u_Button->Power1->setPosition(ButtonPosition::buttonx,ButtonPosition::button5);
}
void BottomManager::DeveloperSetting()
{
	Setting();
	Develop_Setting->Lucky=Sprite::create("UI/button.png");
	Develop_Setting->Lucky->setScale(SCALE);
	Develop_Setting->Lucky->setPosition(buttonx-100,button1);
		
	Develop_Setting->Power=Sprite::create("UI/button.png");
	Develop_Setting->Power->setScale(SCALE);
	Develop_Setting->Power->setPosition(buttonx-100,button2);
		
	Develop_Setting->Upgrade=Sprite::create("UI/button.png");
	Develop_Setting->Upgrade->setScale(SCALE);
	Develop_Setting->Upgrade->setPosition(buttonx-100,button3);

	Develop_Setting->People=Sprite::create("UI/button.png");
	Develop_Setting->People->setScale(SCALE);
	Develop_Setting->People->setPosition(buttonx-100,button4);

	Develop_Setting->Power1=Sprite::create("UI/button.png");
	Develop_Setting->Power1->setScale(SCALE);
	Develop_Setting->Power1->setPosition(buttonx-100,button5);
}
void BottomManager::AddSprite(Node* node)
{
	node->addChild(u_Background->Lucky,0);
	node->addChild(u_Background->Power,0);
	node->addChild(u_Background->Upgrade,0);
	node->addChild(u_Background->People,0);
	node->addChild(u_Background->Power1,0);

	node->addChild(u_Button->Lucky,1);
	node->addChild(u_Button->Power,1);
	node->addChild(u_Button->Upgrade,1);
	node->addChild(u_Button->People,1);
	node->addChild(u_Button->Power1,1);
}
void BottomManager::DeveloperAddSprite(Node* node)
{
	AddSprite(node);
	
	node->addChild(Develop_Setting->Lucky,1);
	node->addChild(Develop_Setting->Power,1);
	node->addChild(Develop_Setting->Upgrade,1);
	node->addChild(Develop_Setting->People,1);
	node->addChild(Develop_Setting->Power1,1);
}
void BottomManager::onTouchBegan(Touch* touch,ScrollView* scroll,bool Developer)
{
	Rect r[5];
	r[4]=u_Button->Lucky->getBoundingBox();
	r[3]=u_Button->Power->getBoundingBox();
	r[2]=u_Button->Upgrade->getBoundingBox();
	r[1]=u_Button->People->getBoundingBox();
	r[0]=u_Button->Power1->getBoundingBox();
		
	Rect scroll_rect[5];
	for(int i=0;i<5;i++)
        scroll_rect[i]=Rect(r[i].origin.x+scroll->getContentOffset().x,
                            r[i].origin.y+scroll->getContentOffset().y,
                            r[i].size.width,r[i].size.height);
	
	
    
    if(scroll_rect[1].containsPoint(touch->getLocation()))
	{
		u_Button->People->setOpacity(200);

	}
    else if(scroll_rect[2].containsPoint(touch->getLocation()))
	{
		u_Button->Upgrade->setOpacity(200);
	}
    else if(scroll_rect[3].containsPoint(touch->getLocation()))
	{
		u_Button->Power->setOpacity(200);

	}
    else if(scroll_rect[4].containsPoint(touch->getLocation()))
	{
		u_Button->Lucky->setOpacity(200);
	}
    else if(scroll_rect[0].containsPoint(touch->getLocation()))
	{
		u_Button->Power1->setOpacity(200);
	}
//-------------------------------------------------------------------------//
	if(Developer)
    {
		r[4]=Develop_Setting->Lucky->getBoundingBox();
		r[3]=Develop_Setting->Power->getBoundingBox();
		r[2]=Develop_Setting->Upgrade->getBoundingBox();
		r[1]=Develop_Setting->People->getBoundingBox();
		r[0]=Develop_Setting->Power1->getBoundingBox();
		
		for(int i=0;i<5;i++){
		scroll_rect[i]=Rect(r[i].origin.x+scroll->getContentOffset().x,
			r[i].origin.y+scroll->getContentOffset().y,
			r[i].size.width,r[i].size.height);
		}
		if(scroll_rect[1].containsPoint(touch->getLocation()))
		{
			Develop_Setting->People->setOpacity(200);

		}else if(scroll_rect[2].containsPoint(touch->getLocation()))
		{
			Develop_Setting->Upgrade->setOpacity(200);
		}else if(scroll_rect[3].containsPoint(touch->getLocation()))
		{
			Develop_Setting->Power->setOpacity(200);

		}else if(scroll_rect[4].containsPoint(touch->getLocation()))
		{
			Develop_Setting->Lucky->setOpacity(200);
		}else if(scroll_rect[0].containsPoint(touch->getLocation()))
		{
			Develop_Setting->Power1->setOpacity(200);
		}

	}
}
