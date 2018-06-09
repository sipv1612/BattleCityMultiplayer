#include "TankMgr.h"

TankMgr* TankMgr::instance = 0;
TankMgr * TankMgr::create()
{
	TankMgr *pRet = new(std::nothrow) TankMgr();
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

TankMgr * TankMgr::GetInstance()
{
	if (!instance)
	{
		instance = TankMgr::create();
	}
	return instance;
}

bool TankMgr::init()
{
	if (!Node::init())
		return false;
	return true;
}


void TankMgr::Update(float deltaTime)
{
	for (int i = 0; i < listTank.size(); i++)
	{
		listTank.at(i)->Update(deltaTime);
	}
}

void TankMgr::Spawn(Team team, float x, float y, eMove dir, bool isCharactor)
{
	if (isCharactor)
	{
		auto tank = Character::create(team);
		tank->SetID(listTank.size());
		this->addChild(tank);
		listTank.pushBack(tank);
		return;
	}
	auto tank = Tank::create(team);
	tank->SetID(listTank.size());
	this->addChild(tank);
	listTank.pushBack(tank);

}

TankMgr::~TankMgr()
{
}

