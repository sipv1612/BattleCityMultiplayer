#include "EndScene.h"



USING_NS_CC;
unsigned int TeamWinner;
Scene* EndScene::createScene( int Winner)
{
    
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	TeamWinner = Winner;
    // 'layer' is an autorelease object
    auto layer = EndScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (TeamWinner == 1)
	{
		auto backGround = cocos2d::Sprite::create("Blue.png");
		backGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		addChild(backGround);
	}
	else
	{
		auto backGround = cocos2d::Sprite::create("Red.png");
		backGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		addChild(backGround);
	}
    return true;
}
void EndScene::menuCloseCallback(Ref* pSender)
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




