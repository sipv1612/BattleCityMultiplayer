#pragma once
class DataGame
{
private:
	char * data;
	int LPTail;
	int LPHead;
	int ret;
public:
	DataGame();
	~DataGame();
	char* GetData();
	void Add(char * value, int size);
	void UpdateLPHead(int value);
	void SetRet(int _ret);
	int GetRet();
	int *GetLPTail();
	int *GetLPHead();

	
};

