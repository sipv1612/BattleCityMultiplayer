#ifndef __OBJECT_H__
#define	__OBJECT_H__


#include "cocos2d.h"

USING_NS_CC;

class Bullet : public ObjectBase
{
private:
	BULLET_STATE bulletState;
	cocos2d::Sprite  *mBullet;
	bool isReset = false;
public:
	Bullet(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	void Init(Owned type, float x, float y, eMove emove);
	void Reset();
	virtual void update(float dt) override;

};

#endif