#include "DataGame.h"
#include "Define.h"


DataGame::DataGame()
{
	data = new char[CMD_BUFSIZE];
	LPTail = 0;
	LPHead = 0;
	ret = 0;
}


DataGame::~DataGame()
{
	delete data;
}

char * DataGame::GetData()
{
	return data;
}

void DataGame::Add(char * value, int size)
{
	if (size + LPTail > CMD_BUFSIZE)
	{
		LPTail = 0;
	}
	memcpy(data + LPTail, value, size);
	LPTail += size;
}

void DataGame::UpdateLPHead(int value)
{
	LPHead += value;
}

void DataGame::SetRet(int _ret)
{
	ret = _ret;
}

int DataGame::GetRet()
{
	return ret;
}

int* DataGame::GetLPTail()
{
	return &LPTail;
}

int* DataGame::GetLPHead()
{
	return &LPHead;
}
