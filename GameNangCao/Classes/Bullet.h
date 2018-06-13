#pragma once
#ifndef BULLET
#define BULLET
#include "BaseObject.h"

class Bullet : public BaseObject
{
private:
	int OwnerID;
public:
	static Bullet* create();
	bool init();

	void Spawn(int _ownerID, Team _team, float _x, float _y, float _serverGameTime, eMove _dir = NONE);
	int getOwnerID();
	void Update(float dt);
	void UpdateMove(float dt);
	bool IsOutOfScreen();
};
#endif // !BULLET