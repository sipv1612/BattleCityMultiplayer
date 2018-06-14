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

	SetBoxSize(MAP_TILED_SIZE, MAP_TILED_SIZE);

	return true;
}


void TerrainObject::SpawnTerrain(TerrainType _type, float _x, float _y, Team _team)
{
	type = _type;
	SetPos(_x, _y);
	switch (_type)
	{
	case BRICK:
		this->setObjectSprite(SPRITE_BRICK);
		this->type = TerrainType::BRICK;
		break;
	case CONCRETE:
		this->setObjectSprite(SPRITE_CONCRETE);
		this->type = TerrainType::CONCRETE;
		break;
	case COMMANDBASE:
		this->team = _team;
		switch (_team)
		{
		case TeamGreen:
			this->setObjectSprite(SPRITE_COMMAND_BASE_GREEN);
			CCLOG("Spawn green");
			break;
		case TeamBlue:
			this->setObjectSprite(SPRITE_COMMAND_BASE_BLUE);
			CCLOG("Spawn blue");
			break;
		case None:
			break;
		default:
			break;
		}
		this->type = TerrainType::COMMANDBASE;
		break;
	default:
		break;
	}

}

TerrainType TerrainObject::GetType()
{
	return type;
}
