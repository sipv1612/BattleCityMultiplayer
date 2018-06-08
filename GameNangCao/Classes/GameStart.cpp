#include "GameStart.h"
#include "SimpleAudioEngine.h"
#include "EndScene.h"
#include <fstream>

USING_NS_CC;
bool RecvedData;
extern int YourPos;
extern Client * client;
Scene* GameStart::createScene()
{
    
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = GameStart::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameStart::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	client->Reset();
#pragma region InitMap
	for (int i = 0; i < 100; i++)
	{
		bullet[i] = new Bullet(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
		bullet[i]->Init(TEAM_1, 0, 0, NONE);
		addChild(bullet[i]);
	}

	for (int i = 0; i <= 3; i++)
	{
		if (i < 2)
		{
			if (i == YourPos)
			{
				character = character = new Character(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
				character->Init(100, 100, 0, eMove::DOWN, 1);
				this->addChild(character);
			}
			else
			{
				Player[i] = new Tank(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
				Player[i]->Init(200, 200, 0, eMove::DOWN, 1);
				this->addChild(Player[i]);
			}
		}
		else
		{
			if (i == YourPos)
			{
				character = character = new Character(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
				character->Init(100, 100, 0, eMove::NONE, 2);
				this->addChild(character);
			}
			else
			{
				Player[i] = new Tank(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
				Player[i]->Init(200, 200, 0, eMove::NONE, 2);
				this->addChild(Player[i]);
			}
		}
	}
	std::ifstream tileMap("Map.txt");
	if (!tileMap.is_open())
	{
		
		CCLOG("Load Map Error !!!!!!!!!\n");
		return false;
	}
	else
	{
		red = 0; silver = 0; robot = 0;
		for (int i = 0; i < 23; i++)
			for (int j = 0; j < 25; j++)
			{
				int tile;
				tileMap >> tile;
				if (tile == 3)
				{
					silverB[silver] = new SilverBrick(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					silverB[silver]->Init(j * 32, 704 - i * 32, 0, NONE);
					addChild(silverB[silver]);
					silver++;
				}
				if (tile == 1)
				{
					redB[red] = new RedBrick(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					redB[red]->Init(j * 32, 704 - i * 32, 0, NONE);
					addChild(redB[red]);
					red++;
				}
				if (tile == 5)
				{
					enemy[robot] = new Enemy(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					enemy[robot]->Init(j * 32, 704 - i * 32, 0, NONE,Owned::TEAM_1);
					addChild(enemy[robot]);
					robot++;
				}
				if (tile == 4)
				{
					enemy[robot] = new Enemy(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					enemy[robot]->Init(j * 32, 704 - i * 32, 0, NONE, Owned::TEAM_2);
					addChild(enemy[robot]);
					robot++;
				}
				if (tile == 6)
				{
					birth[0] = new Birth(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					birth[0]->Init(j * 32, 704 - i * 32, 0, NONE);
					addChild(birth[0]);
				}
				if (tile == 2)
				{
					birth[1] = new Birth(&_world.allPlayer, &_world.allBullet, &_world.allBrick);
					birth[1]->Init(j * 32, 704 - i * 32, 0, NONE);
					addChild(birth[1]);
				}
			}
	}
#pragma endregion
	
#pragma region InitGameObejct
	
	
	

#pragma endregion
	
	//Tạo đối tượng lắng nghe va chạm nếu xảy ra
	this->schedule(schedule_selector(GameStart::run));
    return true;
}
void GameStart::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
void GameStart::update(float delta)
{
	character->UpdateRec();
	broadPhaseBoxA = new Box();
	broadPhaseBoxB = new Box();
	float normalx = 0, normaly = 0;
	for (int i = 0; i < red; i++)
	{
		CollisionClass::GetSweptBroadphaseBox(character->getRecF(), delta, broadPhaseBoxA);
		CollisionClass::GetSweptBroadphaseBox(redB[i]->getRecF(), delta, broadPhaseBoxB);

		if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
		{
			float collisiontime = CollisionClass::SweptAABB(character->getRecF(), redB[i]->getRecF(), normalx, normaly, delta);
			float remainingtime = 1 - collisiontime;
			if (remainingtime > 0)
			{
				character->Stop();
			}
		}
	}
	
	for (int i = 0; i < silver; i++)
	{
		CollisionClass::GetSweptBroadphaseBox(character->getRecF(), delta, broadPhaseBoxA);
		CollisionClass::GetSweptBroadphaseBox(silverB[i]->getRecF(), delta, broadPhaseBoxB);

		if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
		{
			float collisiontime = CollisionClass::SweptAABB(character->getRecF(), silverB[i]->getRecF(), normalx, normaly, delta);
			float remainingtime = 1 - collisiontime;
			if (remainingtime > 0)
			{
				character->Stop();
			}
		}
	}
	character->update(delta);
}
void GameStart::Recv()
{
	
}
void GameStart::run(float delta)
{
	
	client->PacketSend(character->player);
	client->sendData();
	if (character->player.Shooting)
	{
		//CCLOG("Shoot %f\n", deltasend);
		character->player.Shooting = false;
	}

	if (client->recvData())
		RecvedData = true;

	else
		RecvedData = false;

	int teamWin = client->Extras(_world);
	/*if (teamWin != 0)
	{
		CCLOG("%d", teamWin);
		unscheduleUpdate();
		unscheduleAllSelectors();
		client->closeClient();
		client->cleanUpClient();
		auto endScene = EndScene::createScene(teamWin);
		Director::getInstance()->replaceScene(endScene);

	}*/
	update(delta);
}



