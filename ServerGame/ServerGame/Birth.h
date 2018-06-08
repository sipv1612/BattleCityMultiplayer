#pragma once
#include"BaseObject.h"

class Birth : public BaseObject
{
private:
	Owned type;
public:
	Birth() : BaseObject(){}
	void Init(Owned ow, float x, float y)
	{
		this->type = ow;
		box = new Box(x, y, 0, 0, TERRIAN_SIZE, TERRIAN_SIZE);
	}
	Owned getType()
	{
		return this->type;
	}

};
