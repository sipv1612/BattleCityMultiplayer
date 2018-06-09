#include "TankMgr.h"

extern int YourPos;

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

	listPosPlayer.push_back(Pos(320, 50));
	listPosPlayer.push_back(Pos(465, 50));
	listPosPlayer.push_back(Pos(465, 688));
	listPosPlayer.push_back(Pos(320, 688));
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

void TankMgr::InitPlayers()
{
	for (int i = 0; i < 4; i++)
	{
		Team team = i < 2 ? Team::TeamBlue : Team::TeamGreen;
		
		if (i == YourPos)
		{
			this->Spawn(team, listPosPlayer.at(i).x, listPosPlayer.at(i).y, eMove::NONE, true);
		}
		else
		{
			this->Spawn(team, listPosPlayer.at(i).x, listPosPlayer.at(i).y, eMove::NONE, false);
		}
	}
}

void TankMgr::HandleMovePackage(TANK_MOVE package)
{
	auto tank = listTank.at(package.idTank);
	tank->Move(package.dir);
	tank->SetPos(package.posX, package.posY);
}

void TankMgr::HandleDiePackage(TANK_DIE package)
{
	auto tank = listTank.at(package.idTank);
	tank->Die();
	tank->SetPos(package.posX, package.posY);
}

void TankMgr::HandleRevivalPackage(TANK_REVIVAL package)
{
	auto tank = listTank.at(package.idTank);
	tank->Revival();
}

cocos2d::Vector<Tank*> TankMgr::GetTanks()
{
	return listTank;
}

TankMgr::~TankMgr()
{
}


