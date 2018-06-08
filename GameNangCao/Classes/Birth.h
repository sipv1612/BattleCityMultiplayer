#ifndef __BIRTH_H__
#define	__BIRTH_H__


#include "cocos2d.h"
#include "ObjectBase.h"

USING_NS_CC;

class Birth :public ObjectBase
{
public:

	bool isReset = true;
public:
	Birth(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	virtual void Init(float x, float y, float speed, eMove emove);
	void Die();
	virtual void Update(float dt);

};

#endif