#include "Popup.h"

Popup::Popup()
{
    OnThis=false;
}


Popup::~Popup()
{
}

void Popup::Init()
{

    mLayer = Layer::create();
    
    mPopup=Sprite::create("PopMessage/popUp.png");
    mPopup->setPosition(160,240);
    mLayer ->addChild(mPopup,0);
    
    mOkayButton=Sprite::create("PopMessage/okayButton.png");
    mOkayButton->setPosition(160,200);
    mLayer ->addChild(mOkayButton,1);

    mLabel = Label::createWithTTF(mString, "fonts/arial.ttf", 20);
    mLabel->setColor(Color3B::BLACK);
    mLabel->setPosition(160,240);
    
    mLayer->addChild(mLabel,2);
    
    mLabel->setVisible(false);
    mPopup->setVisible(false);
    mOkayButton->setVisible(false);
}
Layer* Popup::on()
{
	OnThis=true;
    mLabel->setVisible(true);
    mPopup->setVisible(true);
    mOkayButton->setVisible(true);
    
    return mLayer;
}
void Popup::off()
{
	OnThis=false;
    RemoveThis();
}

bool Popup::onTouchBegan(Touch *touch)
{
    if(OnThis&&mOkayButton->getBoundingBox().containsPoint(touch->getLocation())){
        mOkayButton->setOpacity(150);
    }
	return false;
}

void Popup::onTouchMoved(Touch *touch)
{
}

void Popup::onTouchEnded(Touch *touch)
{
    if(OnThis&&mOkayButton->getBoundingBox().containsPoint(touch->getLocation())){
        off();
    }
    mOkayButton->setOpacity(255);
}

void Popup::RemoveThis(){
    
    mLabel->setVisible(false);
    mPopup->setVisible(false);
    mOkayButton->setVisible(false);
    
}
