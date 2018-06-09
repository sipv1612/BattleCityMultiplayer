#pragma once
class DataGame
{
private:
	char * data;
	int LPTail;
	int LPHead;
public:
	DataGame();
	~DataGame();
	char* GetData();
	void Add(char * value, int size);
	void UpdateLPHead(int value);
	int GetLPTail();
	int GetLPHead();
	
};

