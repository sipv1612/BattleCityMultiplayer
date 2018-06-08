#include "TankMgr.h"
#include "GlobalVariable.h"

TankMgr* TankMgr::instance = 0;
TankMgr::TankMgr()
{

	listPosPlayer.push_back(Pos(320, 50));
	listPosPlayer.push_back(Pos(465, 50));
	listPosPlayer.push_back(Pos(465, 688));
	listPosPlayer.push_back(Pos(320, 688));

}

TankMgr * TankMgr::GetInstance()
{
	if (!instance)
	{
		instance = new TankMgr();
	}
	return instance;
}

void TankMgr::Update(float deltaTime)
{
	Packing();
	for (int i = 0; i < listTank.size(); i++)
	{
		listTank[i]->Update(deltaTime);
	}
}

void TankMgr::Packing()
{
	for (int i = 0; i < NUM_OF_PLAYER; i++)
	{
		int lpHead = dataRecv[i]->GetLPHead();
		int lpTail = dataRecv[i]->GetLPTail();
		char* data = dataRecv[i]->GetData();
		
		if (lpHead + BYTE_OF_CLIENT > CMD_BUFSIZE)
			lpHead = 0;
		if (lpHead + BYTE_OF_CLIENT <= lpTail)
		{
			TANK_STATE *temp = new TANK_STATE();
			memcpy(temp, data + lpHead, sizeof TANK_STATE);
			if (temp != nullptr)
			{
				listTank[i]->Move(temp->Move);
				if (temp->Shooting)
				{
					listTank[i]->Shoot();
				}
			}
			lpHead += BYTE_OF_CLIENT;
		}
	}
}

void TankMgr::SpawnPlayer()
{
	printf("Spawn Player \n");
	for (int i = 0; i < NUM_OF_PLAYER; i++)
	{
		auto player1 = new Tank();
		Team team = i < 2 ? TEAM_1 : TEAM_2;
		player1->Spawn(team, listPosPlayer[i].x, listPosPlayer[i].y);
		player1->SetID(listTank.size());
		listTank.push_back(player1);
	}
}

void TankMgr::SpawnRobot(Team team, float x, float y)
{
	auto player1 = new Tank();
	player1->Spawn(team, x, y);
	player1->SetRobot();
	player1->SetID(listTank.size());
	listTank.push_back(player1);
}

std::vector<Tank*> TankMgr::GetTanks()
{
	return listTank;
}


TankMgr::~TankMgr()
{
}
