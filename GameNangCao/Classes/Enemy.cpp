#include "Enemy.h"
extern bool RecvedData;

void Enemy::Init(float x, float y, float speed, eMove emove, Owned Team)
{
	
	if (Team == TEAM_1)
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("BlueTeam.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("BlueTeam.plist");
		mEnemy = Sprite::createWithSpriteFrameName("BlueTeam0.png");
		spriteNode->addChild(mEnemy);
		addChild(spriteNode);
		auto animate = cocos2d::Animate::create(Enemy::CreateAnimation("BlueTeam", 8, 0.1));
		animate->retain();
		mEnemy->runAction(cocos2d::RepeatForever::create(animate));		
	}
	else
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("GreenTeam.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("GreenTeam.plist");
		mEnemy = Sprite::createWithSpriteFrameName("GreenTeam0.png");
		spriteNode->addChild(mEnemy);
		addChild(spriteNode);
		auto animate = cocos2d::Animate::create(Enemy::CreateAnimation("GreenTeam", 8, 0.1));
		animate->retain();
		mEnemy->runAction(cocos2d::RepeatForever::create(animate));	
	}
	mEnemy->setScale(0.38, 0.32);
	e_Move = emove;	
	state.Tank = Team;
	state.Move = NONE;
	mEnemy->setPosition(x, y);
	this->allTank->push_back(&state);
	this->scheduleUpdate();
}

void Enemy::update(float delta)
{
	if (state.isDie == 1)
		Die();
	else
		if(isReset == false)
			Reset();

	if (mEnemy->getPosition().distance(Vec2(state.PosX, state.PosY)) > 2)
		mEnemy->setPosition(state.PosX, state.PosY);
	switch (state.Move)
	{
	case eMove::UP:
	{
		mEnemy->setPosition(mEnemy->getPositionX(), mEnemy->getPositionY() + ROBOT_SPEED*delta);
		mEnemy->setRotation(0);
		if (mEnemy->getPositionY() > state.PosY)
			mEnemy->setPositionY(state.PosY);
	}
	break;
	case eMove::DOWN:
	{

		mEnemy->setPosition(mEnemy->getPositionX(), mEnemy->getPositionY() - ROBOT_SPEED*delta);
		mEnemy->setRotation(180);
		if (mEnemy->getPositionY() < state.PosY)
			mEnemy->setPositionY(state.PosY);
	}
	break;
	case eMove::LEFT:
	{

		mEnemy->setPosition(mEnemy->getPositionX() - ROBOT_SPEED*delta, mEnemy->getPositionY());
		mEnemy->setRotation(270);
		if (mEnemy->getPositionX() < state.PosX)
			mEnemy->setPositionX(state.PosX);
	}
	break;
	case eMove::RIGHT:
	{

		mEnemy->setPosition(mEnemy->getPositionX() + ROBOT_SPEED*delta, mEnemy->getPositionY());
		mEnemy->setRotation(90);
		if (mEnemy->getPositionX() > state.PosX)
			mEnemy->setPositionX(state.PosX);
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

void Enemy::Die()
{
	mEnemy->setVisible(false);
	
	if (isReset)
	{
		TBurst* tb = new TBurst();
		tb->init(mEnemy->getPositionX(), mEnemy->getPositionY());
		addChild(tb);
	}
	isReset = false;
}

void Enemy::Reset()
{
	mEnemy->setVisible(true);
	isReset = true;
	mEnemy->setPosition(state.PosX, state.PosY);
}

Vec2 Enemy::getPos()
{
	return mEnemy->getPosition();
}


cocos2d::Animation * Enemy::CreateAnimation(std::string perfixName, int pfamesOrder, float delay)
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

