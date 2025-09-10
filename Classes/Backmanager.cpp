#include "Backmanager.h"

Back::Back()
{

	Visible=false;

	_layer=Layer::create();
	
	_layer->setContentSize(Size(270,200));

	_layer->setPosition(25,150);

	_layer->setVisible(Visible);

	Main=Sprite::create("UI/EndBack.png");
	Main->setAnchorPoint(Point(0,0));
	Main->setScaleX(0.9f);
	
	Okay=Sprite::create("UI/Okay.png");
	Okay->setPosition(75,50);
	
	Cancel=Sprite::create("UI/Cancel.png");
	Cancel->setPosition(200,50);

	_layer->addChild(Okay,1);
	_layer->addChild(Cancel,1);
	_layer->addChild(Main,0);

}

void Back::onTouchBegan(Touch* touch)
{
	if(Visible)
    {
		Point tmp=Point(touch->getLocation().x-25,touch->getLocation().y-150);

		if(Okay->getBoundingBox().containsPoint(tmp))
			Okay->setOpacity(200);
		
        else if(Cancel->getBoundingBox().containsPoint(tmp))
			Cancel->setOpacity(200);
		
	}

}
int Back::onTouchEnded(Touch* touch)
{
	if(Visible)
    {
		Point tmp=Point(touch->getLocation().x-25,touch->getLocation().y-150);
		
		if(Okay->getBoundingBox().containsPoint(tmp))
        {

            Director::getInstance()->end();
#if (CC_PLATFORM_IOS==CC_TARGET_PLATFORM)
            exit(0);
#endif
			Okay->setOpacity(255);
			return 1;

		}
        else if(Cancel->getBoundingBox().containsPoint(tmp))
        {

			Cancel->setOpacity(255);

			_layer->setVisible(false);
			
			Visible=false;
			
			return 2;
		}
	}
	return 0;
}

Layer* Back::Getlayer()
{
	return _layer;
}

void Back::On()
{
	_layer->setVisible(true);
    Visible=true;
}
