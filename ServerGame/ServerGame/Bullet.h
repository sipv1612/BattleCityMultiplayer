#pragma once

#include "BaseObject.h"

class Bullet : public BaseObject
{
protected:
	Owned owned;
	eMove _eMove;
	BULLET_STATE state;
	float timeVisible = 0;
public:
	Bullet()
	{

	}

	Bullet(std::vector<BULLET_STATE*> *_allBullet,
		std::vector<TANK_STATE*> *_allTank,
		std::vector<BRICK_WORLD*> *_allBrick)
		: BaseObject()
	{
		state.isVisible = false;
		_allBullet->push_back(&state);
	}
	Owned getOwn()
	{
		return this->owned;
	}
	void Reset(Owned ow, eMove dir, float x, float y)
	{
		this->owned = ow;
		this->_eMove = dir;
		box->x = x;
		box->y = y;
		state.Own = ow;
		state.isVisible = true;
		timeVisible = 0;
		switch (dir)
		{
		case UP:
			box->width = BULLET_WIDTH;
			box->height = BULLET_HEIGHT;
			box->vx = 0;
			box->vy = -SPEED_BULLET;
			state.Move = UP;
			break;
		case DOWN:
			box->width = BULLET_WIDTH;
			box->height = BULLET_HEIGHT;
			box->vx = 0;
			box->vy = SPEED_BULLET;
			state.Move = DOWN;
			break;
		case LEFT:
			box->width = BULLET_HEIGHT;
			box->height = BULLET_WIDTH;
			box->vx = -SPEED_BULLET;
			box->vy = 0;
			state.Move = LEFT;
			break;
		case RIGHT:
			box->width = BULLET_HEIGHT;
			box->height = BULLET_WIDTH;
			box->vx = SPEED_BULLET;
			box->vy = 0;
			state.Move = RIGHT;
			break;
		default:
			break;
		}
	}
	virtual void Update(float dt)
	{
		if (state.isVisible)
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
			state.PosX = box->x;
			state.PosY = box->y;
			timeVisible += dt;
			if (timeVisible > 15)
				state.isVisible = false;
		}
	}

	void Done()
	{
		this->state.isVisible = false;
	}
	BULLET_STATE getState()
	{
		return this->state;
	}
};