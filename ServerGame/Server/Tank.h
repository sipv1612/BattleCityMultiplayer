#pragma once
#include "Object.h"
class Tank :
	public Object
{
private:
	float timeDie = 0;
	float timeShoot = 0;
	float timeAIRobot = 0;
	float timeAIShoot = 0;
	bool isRobot = false;
	eMove dirShoot = UP;

	void Revival();
	void SendDataRivival();
	void SendDataMove();
	void SendDataDie();
	void UpdateShoot(float deltaTime);
	void UpdateMove(float deltaTime);
	bool IsCanResurrection();
	bool IsPlayerCanShoot();

public:
	Tank();
	~Tank();

	
	bool IsRobot();

	void Die();
	void Reset();
	void SetRobot();
	void SendDataPing();

	void Shoot(bool isPlayer = false);
	void Move(eMove dir = NONE);
	void Update(float deltaTime);
	void AIRobot(float deltaTime);
	void Spawn(Team team, float x, float y, eMove dir = NONE);
};

