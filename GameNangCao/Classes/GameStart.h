#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "ObjectBase.h"
#include "Character.h"
#include "Enemy.h"
#include "RedBrick.h"
#include "SilverBrick.h"
#include "Birth.h"
#include "Tank.h"
#include "Collision.h"
class GameStart : public cocos2d::Layer
{
private:
	Character *character;
	Tank * Player[3];
	Bullet *bullet[100];
	RedBrick *redB[300];
	SilverBrick *silverB[150];
	Box* broadPhaseBoxA;
	Box* broadPhaseBoxB;
	int red, silver, robot;
	Enemy * enemy[10]; 
	Birth * birth[2];
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
