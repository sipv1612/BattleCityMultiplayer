#ifndef __OBJECT_BASE_H__
#define	__OBJECT_BASE_H__


#include "cocos2d.h"
#include "Define.h"
#include "Packet.h"
#include "TBurst.h"
USING_NS_CC;

class ObjectBase :public Sprite
{
protected:

	int Type;
	eMove e_Move = eMove::NONE;
	Box *CRec;
	std::vector<TANK_STATE*> *allTank;
	std::vector<BULLET_STATE*> *allBullet;
	std::vector<BRICK*> *allBrick;
	cocos2d::Sprite* sprite;
	Vec2 veloc = Vec2(0, 0);

public:
	ObjectBase(std::vector<TANK_STATE*> *_allTank,
		std::vector<BULLET_STATE*> *_allBullet,
		std::vector<BRICK*> *_allBrick)
	{
		allTank = _allTank;
		allBullet = _allBullet;
		allBrick = _allBrick;
	
	}
	virtual void Init(float x, float y, float speed, eMove emove, int ID) {};
	virtual void Init(float x, float y, float speed, eMove emove) {};
	virtual void update(float dt) override {};
	virtual void Die() {};
	virtual Box* getRecF() { return new  Box(); };
	
};

#endif