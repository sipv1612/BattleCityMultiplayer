﻿#include "GameStart.h"
#include "SimpleAudioEngine.h"
#include "EndScene.h"
#include "GameManager.h"
#include "Client.h"

USING_NS_CC;
Scene* GameStart::createScene()
{
	loadCaches();
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
	this->addChild(GameManager::create());
	Client::GetInstance()->Reset();

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
	GameManager::GetInstance()->Update(delta);
}
void GameStart::Recv()
{
	Client::GetInstance()->sendData();
	Client::GetInstance()->recvData();
	Client::GetInstance()->Extras();
}
void GameStart::run(float delta)
{
	Recv();
	update(delta);
}



