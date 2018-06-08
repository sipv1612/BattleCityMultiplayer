#ifndef __RED_BRICK_H__
#define	__RED_BRICK_H__


#include "cocos2d.h"
#include "ObjectBase.h"

USING_NS_CC;

class RedBrick :public ObjectBase
{
private:
	BRICK redBrick;
	bool isDie = false;
public:
	RedBrick(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	virtual void Init(float x, float y, float speed, eMove emove);
	Box *getRecF();
	void Die();
	virtual void update(float dt);

};

#endif