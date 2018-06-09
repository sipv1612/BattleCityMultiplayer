#include "TerrainObject.h"

TerrainObject * TerrainObject::create()
{
	TerrainObject *pRet = new(std::nothrow) TerrainObject();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool TerrainObject::init()
{
	if (!BaseObject::init())
		return false;

	SetBoxSize(SIZE_BRICK.width, SIZE_BRICK.height);

	return true;
}

void TerrainObject::SpawnTerrain(TerrainType _type, float _x, float _y)
{
	type = _type;

	switch (_type)
	{
	case BRICK:
		this->setObjectSprite(cocos2d::Sprite::create(SPRITE_BRICK));
		this->type = TerrainType::BRICK;
		break;
	case CONCRETE:
		this->setObjectSprite(cocos2d::Sprite::create(SPRITE_CONCRETE));
		this->type = TerrainType::CONCRETE;
		break;
	default:
		break;
	}

	SetPos(_x, _y);
}

TerrainType TerrainObject::GetType()
{
	return type;
}
