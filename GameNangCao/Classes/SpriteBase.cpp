#include "SpriteBase.h"

void SpriteBase::Init(const std::string& plist, const std::string& imageFile, const std::string& status, int count)
{
	InitResources(plist, imageFile);
}

void SpriteBase::InitAnimate(const std::string& status, int count)
{
	this->m_Animate = CreateAnimate(status, count);
}

cocos2d::Animate* SpriteBase::CreateAnimate(const std::string& status, int count)
{
	cocos2d::Vector<cocos2d::SpriteFrame*> spriteframe;
	for (int i = 0; i < count; i++)
	{
		std::string str = status + "_0" + std::to_string(i + 1) + ".png"; 
		spriteframe.pushBack(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}

	cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(spriteframe, 0.1f);
	auto animate = cocos2d::Animate::create(animation);
	animate->retain();

	return animate;
}

void SpriteBase::InitResources(const std::string& plist, const std::string& imageFile)
{
	addFrameCache(plist, imageFile);
}

void SpriteBase::addFrameCache(const std::string& plist)
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

void SpriteBase::addFrameCache(const std::string& plist, const std::string& imageFile)
{
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, imageFile);
}
