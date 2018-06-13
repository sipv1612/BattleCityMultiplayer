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
	for (int i = 0; i < listTank.size(); i++)
	{
		listTank[i]->Update(deltaTime);
	}
}

void TankMgr::UpdateAIRobot(float deltaTime)
{
	for (int i = 0; i < listTank.size(); i++)
	{
		listTank[i]->AIRobot(deltaTime);
	}
}

void TankMgr::Packing()
{
	int* lpHead = dataRecv->GetLPHead();
	int* lpTail = dataRecv->GetLPTail();
	int ret = dataRecv->GetRet();
	char* data = dataRecv->GetData();
	if (*(lpHead) + ret > CMD_BUFSIZE)
	{
		*(lpHead) = 0;
	}
	while (*(lpHead) < *(lpTail))
	{
		int dataSize = 0;
		memcpy(&dataSize, data + *(lpHead), sizeof(int));
		int packetLimitPerFrame = *(lpHead) + dataSize;
		*(lpHead) += sizeof(int);
		while (*(lpHead) < packetLimitPerFrame)
		{
			RECV_KEY key;
			memcpy(&key, data + *(lpHead), sizeof RECV_KEY);
			*(lpHead) += sizeof RECV_KEY;
			RECV_MOVE_DATA move;
			RECV_SHOOT_DATA shot;
			GET_PING ping;
			switch (key.key)
			{
			case KeySend::Move:
				memcpy(&move, data + *(lpHead), sizeof RECV_MOVE_DATA);
				*(lpHead) += sizeof RECV_MOVE_DATA;
				listTank[move.iD]->Move(move.dir);
				break;
			case KeySend::Shoot:
				memcpy(&shot, data + *(lpHead), sizeof RECV_SHOOT_DATA);
				*(lpHead) += sizeof RECV_SHOOT_DATA;
				listTank[shot.iD]->Shoot(true);
				break;
			case KeySend::Ping:
				memcpy(&ping, data + *(lpHead), sizeof GET_PING);
				*(lpHead) += sizeof GET_PING;
				listTank[ping.iD]->SendDataPing();
			default:
				break;
			}
		}
	}
}

void TankMgr::SpawnPlayer()
{
	printf("Spawn Player \n");
	for (int i = 0; i < 4; i++)
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
	while (!listTank.empty())
	{
		delete listTank.front();
		listTank.erase(listTank.begin());
	}
}
