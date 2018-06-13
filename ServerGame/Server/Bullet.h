#pragma once
#include "Object.h"
class Bullet :
	public Object
{
private:

public:
	Bullet();
	~Bullet();

	void Die();
	void Reset();
	void SendDataDie();
	void SendDataSpawn();
	void Update(float deltaTime);
	void UpdateMove(float deltaTime);
	void Spawn(Team team, float x, float y, eMove dir = NONE);
	bool IsOutOfScreen();


};

