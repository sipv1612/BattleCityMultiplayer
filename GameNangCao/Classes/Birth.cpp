#include "Birth.h"

void Birth::Init(float x, float y, float speed, eMove emove)
{
	sprite = cocos2d::Sprite::create("Birth.png", Rect(0, 0, 32, 32));
	this->addChild(sprite);
	this->setPosition(x, y);
	e_Move = emove;
}

void Birth::Die()
{
}

void Birth::Update(float dt)
{

}