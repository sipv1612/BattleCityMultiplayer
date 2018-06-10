#include "Tank.h"

Tank * Tank::create(Team _team, bool _isRobot)
{
	Tank *pRet = new(std::nothrow) Tank();
	if (pRet && pRet->init(_team, _isRobot))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Tank::init(Team _team, bool _isRobot)
{
	if (!BaseObject::init())
		return false;

	char* str = new char[20];
	switch (_team)
	{
	case TeamGreen:
		sprintf(str, SPRITE_TANK_GREEN_CHILD, 0);
		this->setObjectSprite(Sprite::createWithSpriteFrameName(str));
		this->m_sprite->runAction(RepeatForever::create(getTankMoveAnimate(TeamGreen)));
		break;
	case TeamBlue:
		sprintf(str, SPRITE_TANK_BLUE_CHILD, 0);
		this->setObjectSprite(Sprite::createWithSpriteFrameName(str));
		this->m_sprite->runAction(RepeatForever::create(getTankMoveAnimate(TeamBlue)));
		break;
	case None:
		break;
	default:
		break;
	}
	this->SetBoxSize(TANK_BOX_SIZE, TANK_BOX_SIZE);
	this->setScale(0.5);
	this->SetSpeed(SPEED_TANK);
	return true;
}

bool Tank::IsRobot()
{
	return isRobot;
}

void Tank::Revival()
{
	this->isDie = false;
	this->setVisible(true);
	this->SetPos(originX, originY);
	CCLOG("Respawn%f %f",this->getPosition().x, this->getPosition().y);
}


void Tank::Reset()
{
}

void Tank::SetRobot()
{
	this->isRobot = true;
	this->SetSpeed(SPEED_ROBOT);
}

void Tank::Shoot(bool isPlayer)
{

}

void Tank::UpdateMove(float deltaTime)
{
	if (!IsDie())
	{
		box->x += box->vx * deltaTime;
		box->y += box->vy * deltaTime;
		this->setPosition(box->x, SCREEN_HEIGHT - box->y);
	}
	else
	{

	}

}


void Tank::Update(float deltaTime)
{
	UpdateMove(deltaTime);

}


Tank::~Tank()
{
}
