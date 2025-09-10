#include "Labor.h"

bool Labor::init()
{

	m_sprite=Sprite::create();

	m_point=Point(0,0);

	layer_labor=Layer::create();
	layer_labor->addChild(m_sprite);

	first=true;
	second=false;
	third=false;

	on=false;

	return true;
}

void Labor::setTexture(std::string filepath)
{
	t_first=TextureFactory::Create(filepath+"_1.png");
	t_second=TextureFactory::Create(filepath+"_2.png");
	t_third=TextureFactory::Create(filepath+"_3.png");
}
void Labor::setPosition(const Vec2 &point)
{
	m_sprite->setPosition(point);
	m_point=point;
}
void Labor::setScale(float scale)
{
	m_sprite->setScale(scale);
}
void Labor::texture_update(float delta)
{
	if(!on) return;
	if(first)
    {
	
		m_sprite->setTexture(t_first); 
		dig();
		first=false;
		second=true;
	}
    else if(second)
    {
		m_sprite->setTexture(t_second);
		second=false;
		third=true;
	}
    else
    {
		m_sprite->setTexture(t_third);
		third=false;
		first=true;
	}

}
void Labor::Add()
{
	int x[8]={50,100,130,170,200,250,260,290};
    if(number%2==0)
        m_sprite->setFlippedX(true);
	setPosition(Point(x[number-1],300));
	setScale(0.75);
	on=true;
}
void Labor::dig()
{
	int *a=&Defaultmanager::MinesHealth;
	int power= Defaultmanager::LaborPower;
	if(power<30)
		*a-=power*power;
	else 
		*a-=(power+1)*power*2-800;
}
void Labor::setnumber(int a)
{
	number=a;
    if(number%2==1)
        m_sprite->setTexture("Labor/labor2_1.png");
}
