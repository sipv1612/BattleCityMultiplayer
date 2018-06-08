#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameStart.h"
#include "Box2D\Box2D.h"

class HelloWorld : public cocos2d::Layer
{
private:
	
public:
    static cocos2d::Scene* createScene();
	cocos2d::Sprite *mTank[4];
    virtual bool init();
	bool isTeam = false;
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
