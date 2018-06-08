#pragma once

#include "Define.h"

class BaseObject {
protected:
	Box* box;
	std::vector<BULLET_STATE*> *allBullet;
	std::vector<TANK_STATE*> *allTank;
	std::vector<BRICK_WORLD*> *allBrick;
public:
	BaseObject()
	{
		box = new Box();
	}

	BaseObject(std::vector<BULLET_STATE*> *_allBullet,
		std::vector<TANK_STATE*> *_allTank, std::vector<BRICK_WORLD*> *_allBrick,
		 float x, float y, float vx, float vy, int width, int height)
	{
		box = new Box(x, y, vx, vy, width, height);
		allBullet = _allBullet;
		allBrick = _allBrick;
		allTank = _allTank;
		
	}
	virtual void Move(eMove drc)
	{
		switch (drc)
		{
		case eMove::UP:
			box->vx = 0;
			box->vy = TANK_SPEED;
			break;
		case eMove::DOWN:
			box->vx = 0;
			box->vy = -TANK_SPEED;
			break;
		case eMove::LEFT:
			box->vx = -TANK_SPEED;
			box->vy = 0;
			break;
		case eMove::RIGHT:
			box->vx = TANK_SPEED;
			box->vy = 0;
			break;
		default:
			break;
		}
	}

	virtual Box* GetBox()
	{
		return box;
	}
};