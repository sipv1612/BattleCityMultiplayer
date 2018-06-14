#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Define.h"

class EndScene : public cocos2d::Layer
{
public:
	Team teamWin;
    static cocos2d::Scene* createScene(Team Winer);

    virtual bool init();
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(EndScene);
};

#endif // __HELLOWORLD_SCENE_H__