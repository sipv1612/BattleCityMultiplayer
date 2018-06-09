#pragma once
#ifndef BASE_OBJECT
#define BASE_OBJECT
#include "Define.h"

class BaseObject : public cocos2d::Node
{
protected:
	int ID;
	eMove moveDir;
	Box *box;
	Team team;
	cocos2d::Sprite *m_sprite;
	float originX;
	float originY;
	float speedMove;
	bool isDie;
public:
	static BaseObject* create(Team _team = Team::None);
	virtual bool init() override;

	void setObjectSprite(cocos2d::Sprite* _sprite);
	virtual void Move(eMove dir = NONE);
	virtual void SetSpeed(float speed);
	virtual void Die();
	virtual void Reset();
	virtual void SetID(int id);
	virtual void Update(float deltaTime);
	virtual void Spawn(Team team, float x, float y, eMove dir = NONE);
	virtual void SetPos(float x, float y);
	virtual void SetVel(float x, float y);
	virtual void SetBoxSize(int width, int _height);
	virtual void AABBHandle(float deltaTime, float collisionTime);
	virtual Box* GetBox();
	virtual Team GetTeam();
	virtual bool IsDie();

};
#endif // !BASE_OBJECT