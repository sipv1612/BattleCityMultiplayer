#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "cocos2d.h"
#include <string.h>

class SpriteBase
{
public:
	void Init(const std::string& plist, const std::string& imagefile, const std::string& status, int count);
	cocos2d::Animate* m_Animate;
	cocos2d::Sprite m_Sprite;
	cocos2d::Animate* CreateAnimate(const std::string& status, int count);
private:
	void InitResources(const std::string& plist, const std::string& imagefile);
	void InitAnimate(const std::string& status, int count);
	void addFrameCache(const std::string& plist);
	void addFrameCache(const std::string& plist, const std::string& imagefile);
	
};

#endif
