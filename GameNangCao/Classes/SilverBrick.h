#ifndef __SILVER_BRICK_H__
#define	__SILVER_BRICK_H__


#include "cocos2d.h"

USING_NS_CC;

class SilverBrick:public ObjectBase
{
public:


public:
	SilverBrick(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) { };
	virtual void Init(float x, float y, float speed, eMove emove);

	virtual void Update(float dt);
	Box *getRecF();
};

#endif