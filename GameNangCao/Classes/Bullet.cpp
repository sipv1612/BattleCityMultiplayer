#include "Bullet.h"

USING_NS_CC;

Bullet * Bullet::create()
{
	Bullet *pRet = new(std::nothrow) Bullet();
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

bool Bullet::init()
{
	if (!BaseObject::init())
		return false;

	this->setObjectSprite(Sprite::create(SPRITE_BULLET));
	this->SetSpeed(SPEED_BULLET);
	OwnerID = -1;

	return true;
}

void Bullet::Spawn(int _ownerID, Team _team, float _x, float _y, eMove _dir)
{
	this->setObjectSprite(Sprite::create(SPRITE_BULLET));
	OwnerID = _ownerID;
	isDie = false;
	SetSpeed(SPEED_BULLET);
	SetPos(_x, _y);
	Move(_dir);
	switch (_dir)
	{
	case UP:
	case DOWN:
		SetBoxSize(SIZE_BULLET.width, SIZE_BULLET.height);
		break;
	case LEFT:
	case RIGHT:
		SetBoxSize(SIZE_BULLET.height, SIZE_BULLET.width);
		break;
	default:
		printf("NONEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
		break;
	}
}

int Bullet::getOwnerID()
{
	return OwnerID;
}

void Bullet::Update(float dt)
{
	UpdateMove(dt);
}

void Bullet::UpdateMove(float dt)
{
	if (!IsDie())
	{
		if (IsOutOfScreen())
		{
			Die();
		}
		box->x += box->vx * dt;
		box->y += box->vy * dt;
		this->setPosition(box->x, SCREEN_HEIGHT - box->y);
	}

}

bool Bullet::IsOutOfScreen()
{
	return (box->x < 0 || box->x + box->width > SCREEN_WIDTH || box->y < 0 || box->y + box->height > SCREEN_HEIGHT);
}
