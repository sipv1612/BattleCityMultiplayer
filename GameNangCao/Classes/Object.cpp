#include "Bullet.h"

void Bullet::Init(Owned type, float x, float y, eMove emove)
{
	
	mBullet = Sprite::create("EnemyBullet.png");
	addChild(mBullet);
	mBullet->setScale(0.3);
	e_Move = emove;
	mBullet->setPosition(x, y);
	bulletState.IsVisible = false;
	this->allBullet->push_back(&bulletState);
	this->scheduleUpdate();
}

void Bullet::Reset()
{
	mBullet->setPosition(bulletState.PosX - 15, 720 - bulletState.PosY);
	this->setVisible(true);
}

void Bullet::update(float dt)
{
	if (bulletState.IsVisible)
	{
		if (!isReset)
		{
			Reset();
			isReset = true;
		}
		switch (bulletState.Move)
		{
		case eMove::UP:
		{
			mBullet->setPosition(mBullet->getPositionX(), mBullet->getPositionY() + SPEED_BULLET*dt);
			
			mBullet->setRotation(0);
		}
		break;
		case eMove::DOWN:
		{
			mBullet->setPosition(mBullet->getPositionX(), mBullet->getPositionY() - SPEED_BULLET * dt);
		
			mBullet->setRotation(180);
		}
		break;
		case eMove::LEFT:
		{
			mBullet->setPosition(mBullet->getPositionX() - SPEED_BULLET*dt, mBullet->getPositionY());
			
			mBullet->setRotation(270);
		}
		break;
		case eMove::RIGHT:
		{
			mBullet->setPosition(mBullet->getPositionX() + SPEED_BULLET*dt, mBullet->getPositionY());
			
			mBullet->setRotation(90);
		}
		break;
		case eMove::DIE:
		{

		}
		break;
		default:
			break;
		}
	}
	else
	{
		this->setVisible(false);
		isReset = false;
	}

}
