#include "SilverBrick.h"

void SilverBrick::Init(float x, float y, float speed, eMove emove)
{
	sprite = cocos2d::Sprite::create("SilverBrick.png", Rect(0, 0, 32, 32));
	this->addChild(sprite);
	this->setPosition(x, y);	
	this->CRec = new Box(x, y, 0, 0, 32, 32);
	e_Move = emove;

}

void SilverBrick::Update(float dt)
{

}

Box * SilverBrick::getRecF()
{
	return this->CRec;
}
