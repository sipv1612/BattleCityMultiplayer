#ifndef __TANK_H__
#define	__TANK_H__

#include "ObjectBase.h"

USING_NS_CC;

class Tank : public ObjectBase
{
public:
	cocos2d::Sprite *mTank, *mGun;
	bool isKeyDown = false;
	bool isRun = false;
	bool isReset = true;
	std::string perfix;
	TANK_STATE state;
public:
	Tank(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	void InitTank(float x, float y, int team);
	void InitGun(float x, float y, int team);
	virtual void Init(float x, float y, float speed, eMove emove, int Team);
	void tankMove(float delta);
	virtual void update(float delta) override;
	void tankAnimationMove();
	void tankAnimationIdle();
	void followObject();
	void Reset();
	void Die();
	void ProcessTank(TANK_STATE state);
	cocos2d::Animation * CreateAnimation(std::string perfixName, int pfamesOrder, float delay);

};

#endif