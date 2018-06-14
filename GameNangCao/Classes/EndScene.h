#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Define.h"

class EndScene : public cocos2d::Layer
{
private:
	Team teamWin;
public:
    static cocos2d::Scene* createScene(Team Winer);

    virtual bool init(Team _teamWin);
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
};

#endif // __HELLOWORLD_SCENE_H__