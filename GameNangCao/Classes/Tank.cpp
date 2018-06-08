#include "Tank.h"
extern bool RecvedData;
void Tank::InitTank(float x, float y, int team)
{
	if (team == 1)
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("EnemyMove.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("EnemyMove.plist");
		mTank = Sprite::createWithSpriteFrameName("Enemy0.png");
		addChild(spriteNode);
		spriteNode->addChild(mTank);
		mTank->setRotation(180);
		auto animate = cocos2d::Animate::create(Tank::CreateAnimation("Enemy", 5, 0.1));
		animate->retain();
		mTank->runAction(cocos2d::RepeatForever::create(animate));
		perfix = "Enemy";
		
	}
	if (team == 2)
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("RedTank.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("RedTank.plist");
		mTank = Sprite::createWithSpriteFrameName("Tank0.png");
		addChild(spriteNode);
		spriteNode->addChild(mTank);
		auto animate = cocos2d::Animate::create(Tank::CreateAnimation("Tank", 5, 0.1));
		animate->retain();
		mTank->runAction(cocos2d::RepeatForever::create(animate));
		perfix = "Tank";
	}
	mTank->setPosition(x, y);
	mTank->setScale(0.15);
	mTank->setAnchorPoint(Vec2(0.5, 0.5));
}

void Tank::InitGun(float x, float y, int team)
{
	if (team == 1)
	{
		mGun = Sprite::create("EnemyGun.png");
		mGun->setRotation(180);
	}
	if(team == 2)
		mGun = Sprite::create("RedGun.png");
	mGun->setPosition(x, y);
	mGun->setAnchorPoint(Vec2(0.5f, 0.231f));
	mGun->setScale(0.15);
	addChild(mGun, 0);
}

void Tank::Init(float x, float y, float speed, eMove emove,  int Team)
{
	InitTank(x, y, Team);
	InitGun(x, y, Team);
	e_Move = emove;
	isRun = false;
	allTank->push_back(&state);
	this->scheduleUpdate();
}

void Tank::tankMove(float delta)
{
	
	switch (e_Move)
	{
	case eMove::UP:
	{

		mTank->setPosition(mTank->getPositionX(), mTank->getPositionY() + SPEED_TANK*delta);
		mTank->setRotation(0);
		mGun->setRotation(0);
		if (mTank->getPositionY() > state.PosY)
			mTank->setPositionY(state.PosY);
	}
	break;
	case eMove::DOWN:
	{

		mTank->setPosition(mTank->getPositionX(), mTank->getPositionY() - SPEED_TANK*delta);
		
		mTank->setRotation(180);
		mGun->setRotation(180);
		if (mTank->getPositionY() < state.PosY)
			mTank->setPositionY(state.PosY);
	}
	break;
	case eMove::LEFT:
	{

		mTank->setPosition(mTank->getPositionX() - SPEED_TANK*delta, mTank->getPositionY());
		
		mTank->setRotation(270);
		mGun->setRotation(270);
		if (mTank->getPositionX() < state.PosX)
			mTank->setPositionX(state.PosX);
	}
	break;
	case eMove::RIGHT:
	{

		mTank->setPosition(mTank->getPositionX() + SPEED_TANK*delta, mTank->getPositionY());
		mTank->setRotation(90);
		mGun->setRotation(90);
		if (mTank->getPositionX() > state.PosX)
			mTank->setPositionX(state.PosX);
	}
	break;
	case eMove::DIE:
	{

	}
	break;
	case eMove::NONE:
	{
		
	}
	break;
	default:
		break;
	}
}

void Tank::update(float dt)
{
	
	if (state.isDie == 1)
		Die();
	else
	{
		if (isRun)
		{
			if (isKeyDown == false)
				tankAnimationMove();
			tankMove(dt);
		}
		else
		{
			if (isKeyDown)
				tankAnimationIdle();
			mTank->setPosition(Vec2(state.PosX, state.PosY));
		}
		if (isReset == false)
			Reset();
	}
	e_Move = NONE;
	ProcessTank(state);
	followObject();

}

void Tank::tankAnimationMove()
{
	mTank->stopAllActions();
	auto animate = cocos2d::Animate::create(Tank::CreateAnimation(perfix, 5, 0.1));
	animate->retain();
	mTank->runAction(cocos2d::RepeatForever::create(animate));
	isKeyDown = true;
}

void Tank::tankAnimationIdle()
{
	mTank->stopAllActions();
	auto animate = cocos2d::Animate::create(Tank::CreateAnimation(perfix, 1, 0.1));
	animate->retain();
	mTank->runAction(animate);
	isKeyDown = false;
}

void Tank::followObject()
{
	this->mGun->setPosition(mTank->getPosition());
}

void Tank::Reset()
{
	mTank->setVisible(true);
	mGun->setVisible(true);
	isReset = true;
	mTank->setPosition(state.PosX, state.PosY);
}

void Tank::Die()
{
	mTank->setVisible(false);
	mGun->setVisible(false);
	if (isReset)
	{
		TBurst* tb = new TBurst();
		tb->init(mTank->getPositionX(), mTank->getPositionY());
		addChild(tb);
	}
	isReset = false;
}

void Tank::ProcessTank(TANK_STATE state)
{
	this->e_Move = state.Move;
	switch (this->e_Move)
	{
	case eMove::DOWN:		
	case eMove::UP:		
	case eMove::LEFT:		
	case eMove::RIGHT:
		isRun = true;
		break;
	default:
		isRun = false;
		break;
	}
	
}

cocos2d::Animation * Tank::CreateAnimation(std::string perfixName, int pfamesOrder, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < pfamesOrder; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		std::string st = perfixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(st);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}

