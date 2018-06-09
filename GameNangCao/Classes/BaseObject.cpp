#include "BaseObject.h"

BaseObject*  BaseObject::create(Team _team)
{
	BaseObject *pRet = new(std::nothrow) BaseObject();
	if (pRet && pRet->init())
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

bool BaseObject::init()
{
	if (!Node::init())
		return false;

	m_sprite = nullptr;
	box = new Box();
	team = Team::None;
	moveDir = eMove::NONE;
	originX = 0;
	originX = 0;
	speedMove = 0;
	ID = 0;
	isDie = false;
	this->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	return true;

}

void BaseObject::setObjectSprite(cocos2d::Sprite *_sprite)
{
	this->m_sprite = _sprite;
	this->addChild(_sprite);
}

void BaseObject::Move(eMove dir)
{
	moveDir = dir;
	switch (moveDir)
	{
	case eMove::UP:
		SetVel(0, -speedMove);
		break;
	case eMove::DOWN:
		SetVel(0, speedMove);
		break;
	case eMove::LEFT:
		SetVel(-speedMove, 0);
		break;
	case eMove::RIGHT:
		SetVel(speedMove, 0);
		break;
	default:
		SetVel(0, 0);
		break;
	}
}

void BaseObject::SetSpeed(float speed)
{
	speedMove = speed;
}

void BaseObject::Die()
{
	isDie = true;
	//add explosion
	Animate *explosionAnimate = getExplosionAnimate();
	auto autoHideParent = CallFuncN::create(
		[&](Node *sender)
	{
		sender->getParent()->setVisible(false);
	});
	m_sprite->runAction(Sequence::create(explosionAnimate, autoHideParent, nullptr));
}

void BaseObject::Reset()
{
}

void BaseObject::SetID(int id)
{
	ID = id;
}

void BaseObject::Update(float deltaTime)
{

}

void BaseObject::Spawn(Team _team, float _x, float _y, eMove _dir)
{
	SetPos(_x, _y);
	moveDir = _dir;
	team = _team;
}

void BaseObject::SetPos(float _x, float _y)
{
	box->x = _x;
	box->y = _y;
	this->setPosition(_x, _y);
}

void BaseObject::SetVel(float _x, float _y)
{
	box->vx = _x;
	box->vy = _y;
}

void BaseObject::SetBoxSize(int _width, int _height)
{
	box->width = _width;
	box->height = _height;
}

void BaseObject::AABBHandle(float deltaTime, float collisionTime)
{
	box->x += box->vx * collisionTime * deltaTime;
	box->y += box->vy * collisionTime * deltaTime;
	box->vx = 0;
	box->vy = 0;
}

bool BaseObject::IsOutOfScreen()
{
	return (box->x < 0 || box->x + box->width > SCREEN_WIDTH || box->y < 0 || box->y + box->height > SCREEN_HEIGHT);
}

Box*  BaseObject::GetBox()
{
	return box;
}

Team BaseObject::GetTeam()
{
	return team;
}

bool BaseObject::IsDie()
{
	return isDie;
}