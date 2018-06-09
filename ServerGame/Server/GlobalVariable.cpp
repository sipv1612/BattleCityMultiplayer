#include "GlobalStruck.h"
#include "DataGame.h"

bool gameRunning = false;
bool gameEnded = false;
int numOfPlayer = 0;
char * dataSendBuffer = new char[DATA_BUFSIZE];
int LPDataSendBuffer = sizeof(int);

HANDLE networkProc;
HANDLE gameProc;
DWORD Total;
FD_SET WriteSet;
FD_SET ReadSet;
LPSOCKET_INFORMATION socketArray[FD_SETSIZE];
DataGame* dataRecv = new DataGame();
CRITICAL_SECTION criticalDataRecv;
