#include "HelloWorldScene.h"
#include "Client.h"


USING_NS_CC;
int YourPos;
Scene* HelloWorld::createScene()
{
    
	// 'scene' is an autorelease object
	auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Intro = cocos2d::Sprite::create("Intro.png");
	Intro->setPosition(visibleSize.width / 2, visibleSize.height / 2 +200);
	Intro->setScale(0.5);
	addChild(Intro);
	auto mText = cocos2d::Sprite::create("Waiting.png");
	mText->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mText);
	for (int i = 0; i < 4; i++)
	{
		if(i < 2)
			mTank[i] = cocos2d::Sprite::create("BlueTeam2.png");
		else
			mTank[i] = cocos2d::Sprite::create("RedTeam2.png");
		mTank[i]->setScale(0.175);
		mTank[i]->setPosition(visibleSize.width / 2 - 70 + i * 35, visibleSize.height / 2 - 100);
		mTank[i]->setVisible(false);
		addChild(mTank[i]);
	}
	Client::GetInstance();
	this->scheduleUpdate();
    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
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
void HelloWorld::update(float delta)
{
	if (Client::GetInstance()->recvData())
	{

		if (Client::GetInstance()->getTeam() == 1)
		{
			isTeam = true;
			YourPos = 0;

		}
		if (Client::GetInstance()->getTeam() == 2)
		{
			if (isTeam == false)
			{
				YourPos = 1;
				isTeam = true;
			}
			
		}
		if (Client::GetInstance()->getTeam() == 3)
		{
			if (isTeam == false)
			{
				YourPos = 2;
				isTeam = true;
			}
		}
		if (Client::GetInstance()->getTeam() == 4)
		{
			if (isTeam == false)
			{
				YourPos = 3;
			}
			auto endScene = GameStart::createScene();
			Director::getInstance()->replaceScene(endScene);
		}
		for (int i = 0; i < Client::GetInstance()->getTeam(); i++)
		{
			mTank[i]->setVisible(true);
		}
	}
}




