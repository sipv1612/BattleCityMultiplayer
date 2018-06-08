#ifndef __ENEMY_H__
#define	__ENEMY_H__

#include "ObjectBase.h"

USING_NS_CC;

class Enemy : public ObjectBase
{
public:

	TANK_STATE state;
	bool isReset = true;
	cocos2d::Sprite *mEnemy;
public:
	Enemy(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	virtual void Init(float x, float y, float speed, eMove emove, Owned Team);
	virtual void update(float dt) override;
	virtual void Die();
	virtual void Reset();
	Vec2 getPos();
	cocos2d::Animation * CreateAnimation(std::string perfixName, int pfamesOrder, float delay);


};

#endif