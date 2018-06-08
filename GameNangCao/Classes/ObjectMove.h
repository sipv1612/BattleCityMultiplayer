#ifndef __OBJECT_MOVE_H__
#define	__OBJECT_MOVE_H__


#include "cocos2d.h"
#include "Define.h"
#include "SpriteBase.h"
#include "ObjectBase.h"

USING_NS_CC;

class ObjectMove :public ObjectBase
{
public:


	std::map<eMove, Animate*> arrAnimate;

public:

	virtual void Init(float x, float y, float speed, eMove emove){};

	virtual void update(float dt) {};

};

#endif