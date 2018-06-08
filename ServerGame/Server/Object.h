#pragma once
#include "Define.h"
#include "Box.h"
#include "GlobalStruck.h"
class Object
{
protected:
	Box * box;
	Team team;
	eMove moveDir;
	float originX;
	float originY;
	float speedMove;
	bool isDie;
	int iD;
	
public:
	Object();
	virtual ~Object();
	virtual void Init();
	virtual void Move(eMove dir = NONE);
	virtual void SetSpeed(float speed);
	virtual void Die();
	virtual void Reset();
	virtual void SetID(int id);
	virtual void Update(float deltaTime);
	virtual void Spawn(Team team, float x, float y, eMove dir = NONE);
	virtual void SetPos(float _x, float _y);
	virtual void SetVel(float _x, float _y);
	virtual void SetBoxSize(int _width, int _height);
	virtual void AABBHandle(float deltaTime, float collisionTime);
	virtual bool IsDie();

	virtual Box * GetBox();
	virtual Team GetTeam();

};

