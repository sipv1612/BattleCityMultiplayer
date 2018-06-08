#ifndef _TBURST_H_
#define _TBURST_H_

#include "cocos2d.h"

USING_NS_CC;
class TBurst : public cocos2d::Sprite
{
private:
	cocos2d::Sprite * mBurst;
	float _Time;
public:
	TBurst();
	~TBurst();
	bool init(float x , float y);
	void update(float delta);
	cocos2d::Animation * CreateAnimation(std::string perfixName, int pfamesOrder, float delay);
};
#endif // !_TBURST_H_