#pragma once

#include "BaseObject.h"
#include "Bullet.h"

class PlayerTank : public BaseObject
{
private:
	Owned owned;
	eMove _eMove;
	float timeDie;
	TANK_STATE tank;
	float PosX, PosY;
public:
	PlayerTank() : BaseObject()
	{
		
	}

	PlayerTank(std::vector<BULLET_STATE*> *_allBullet,
		std::vector<TANK_STATE*> *_allTank,
		std::vector<BRICK_WORLD*> *_allBrick, Owned ow, float x, float y, int width, int height, eMove dir)
		: BaseObject(_allBullet, _allTank, _allBrick, x, y, 0, 0, width, height)
	{

		
		owned = ow;
		_eMove = dir;
		tank.Tank = ow;
		tank.isDie = false;
		PosX = x;
		PosY = y;
		allTank->push_back(&tank);

	}

	void BeProtected() {}
	Owned getOwn()
	{
		return this->owned;
	}
	bool isDie()
	{
		return tank.isDie;
	}
	virtual void Move(eMove drc, float Speed)
	{
		switch (drc)
		{
		case eMove::UP:
			box->vx = 0;
			box->vy = -Speed;
			_eMove = drc;
			break;
		case eMove::DOWN:
			box->vx = 0;
			box->vy = Speed;
			_eMove = drc;
			break;
		case eMove::LEFT:
			box->vx = -Speed;
			box->vy = 0;
			_eMove = drc;
			break;
		case eMove::RIGHT:
			box->vx = Speed;
			box->vy = 0;
			_eMove = drc;
			break;
		default:
			box->vx = 0;
			box->vy = 0;
			break;
		}
		tank.Move = drc;
	}
	void Die()
	{		
		tank.isDie = true;
	}
	void Reset()
	{
		timeDie = 0;
		box->x = PosX;
		box->y = PosY;
		tank.isDie = false;
	}
	virtual void Update(float dt)
	{
		if (!tank.isDie)
		{
			if (box->x < 0 || box->x + box->width > SCREEN_WIDTH)
			{
				if (box->x < 0)
					box->x = 0;
				if (box->x + box->width > SCREEN_WIDTH)
					box->x = SCREEN_WIDTH - box->width;
				box->vx = 0;
			}
			if (box->y < 0 || box->y + box->height > SCREEN_HEIGHT)
			{
				if (box->y < 0)
					box->y = 0;
				if (box->y + box->height > SCREEN_HEIGHT)
					box->y = SCREEN_HEIGHT - box->height;
				box->vy = 0;
			}
			box->x += box->vx * dt;
			box->y += box->vy * dt;
			tank.PosX = box->x;
			tank.PosY = 704 - box->y;
		}
		else
		{
			timeDie += dt;
			box->x = 0;
			box->vx = 0;
			box->y = 0;
			box->vy = 0;
			tank.Move = NONE;
			tank.PosX = box->x;
			tank.PosY = box->y;
			if (timeDie > 3)
			{
				Reset();
			}
			
		}

	}
	virtual void Shoot(Bullet** bullet, int nBullet, eMove _sideShoot)
	{
		
		for (int i = 0; i < nBullet; i++)
		{
			if (bullet[i]->getState().isVisible == false)
			{

				float x = 0, y = 0;
				x = box->x + TANK_SIZE / 2;
				y = box->y + TANK_SIZE / 2;
				bullet[i]->Reset(this->owned, _sideShoot, x, y);
				break;
			}
		}
	}
};