#pragma once

#include "BaseObject.h"

class TerrianObject : public BaseObject
{
private:
	TerrianType type;
	int lvlToDestroy; //level bullet to destroy this object
	BRICK_WORLD brick;
public:
	TerrianObject() {}
	TerrianObject(std::vector<BULLET_STATE*> *_allBullet,
		std::vector<TANK_STATE*> *_allTank,
		std::vector<BRICK_WORLD*> *_allBrick)
	{
		this->allBrick = _allBrick;
		this->allBullet = _allBullet;
		this->allTank = _allTank;
	}
	void Init(TerrianType ow, float x, float y)
	{
		this->type = ow;

		if (ow == REB)
		{
			brick.ID = 1;
			brick.isDie = false;
			brick.PosX = x;
			brick.PosY = y;
			allBrick->push_back(&brick);
		}

		box = new Box(x, y, 0, 0, TERRIAN_SIZE, TERRIAN_SIZE);


	}
	TerrianType GetType()
	{
		return type;
	}

	void Done()
	{
		brick.isDie = true;
	}
	BRICK_WORLD getState()
	{
		return this->brick;
	}
};