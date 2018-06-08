#include "TBurst.h"

TBurst::TBurst()
{
}

TBurst::~TBurst()
{
}

bool TBurst::init(float x, float y)
{
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("tburst.png");
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("tburst.plist");
	mBurst = Sprite::createWithSpriteFrameName("TBurst_0.png");
	addChild(spriteNode);
	spriteNode->addChild(mBurst);
	mBurst->setPosition(x, y);
	mBurst->setScale(1);
	mBurst->setAnchorPoint(Vec2(0.5, 0.5));
	auto animate = cocos2d::Animate::create(TBurst::CreateAnimation("TBurst_", 5, 0.05));
	animate->retain();
	_Time = 0;
	mBurst->runAction(animate);
	scheduleUpdate();
	return true;
}

void TBurst::update(float delta)
{
	_Time += delta;
	if (_Time > 0.3)
	{
		mBurst->setVisible(false);
		removeFromParent();
	}
}

cocos2d::Animation * TBurst::CreateAnimation(std::string perfixName, int pfamesOrder, float delay)
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
