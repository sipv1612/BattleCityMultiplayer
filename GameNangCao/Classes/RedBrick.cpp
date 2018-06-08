#include "RedBrick.h"
extern bool RecvedData;
void RedBrick::Init(float x, float y, float speed, eMove emove)
{
	sprite = cocos2d::Sprite::create("Brick.png", Rect(0, 0, 32, 32));
	
	sprite->setPosition(x, y);
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->CRec = new Box(x, y, 0, 0, 32, 32);
	e_Move = emove;
	this->addChild(sprite);
	allBrick->push_back(&redBrick);
	this->scheduleUpdate();
}

Box * RedBrick::getRecF()
{
	return this->CRec;
}

void RedBrick::Die()
{
	
	if (!isDie)
	{
		sprite->setVisible(false);
		TBurst* tb = new TBurst();
		tb->init(sprite->getPositionX(), sprite->getPositionY());
		addChild(tb);
		this->unscheduleUpdate();
	}
	isDie = true;
}

void RedBrick::update(float dt)
{
	if (redBrick.isDie == true)
	{
		Die();
	}
	else
	{
		//sprite->setPosition(redBrick.PosX,704 - redBrick.PosY);
		this->CRec->x = sprite->getPositionX();
		this->CRec->y = sprite->getPositionY();
	}
}