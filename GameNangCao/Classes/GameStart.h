#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "SilverBrick.h"
#include "Collision.h"
class GameStart : public cocos2d::Layer
{
private:
	Character *character;
	SilverBrick *silverB[150];
	Box* broadPhaseBoxA;
	Box* broadPhaseBoxB;
	int red, silver, robot;
	UPDATE_WORLD _world;
	float deltasend;
	
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void update(float delta);
	void run(float delta);
	

	
	void Recv();
    // implement the "static create()" method manually
    CREATE_FUNC(GameStart);
};

#endif // __GAMESTART_SCENE_H__
