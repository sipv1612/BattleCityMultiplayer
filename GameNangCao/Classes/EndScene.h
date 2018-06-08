#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class EndScene : public cocos2d::Layer
{
private:
	
public:
    static cocos2d::Scene* createScene( int Winer);

    virtual bool init();
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(EndScene);
};

#endif // __HELLOWORLD_SCENE_H__