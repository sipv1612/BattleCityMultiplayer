#ifndef _CLIENT_H_
#define _CLIENT_H_


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include "cocos2d.h"
#include "Define.h"
using namespace std;

class Client
{
private:

	char  szServer[128],                          // Server to connect to
		szMessage[1024];                      // Message to send to sever
	char* _packet;
	unsigned int _size;
	int   iPort = DEFAULT_PORT;    // Port on server to connect to
	DWORD dwCount = DEFAULT_COUNT; // Number of times to send message
	BOOL  bSendOnly = FALSE;                        // Send data only; don't receive
	WSADATA       wsd;
	SOCKET        sClient;
	char          szBuffer[DEFAULT_BUFFER];
	int           ret, i;
	struct sockaddr_in server;
	struct hostent    *host = NULL;
	char Buffer[BUFFER_SIZE];
	int LPTail = 0;
	int LPHead = 0;
	int dataSize = 0;
	static Client * instance;
	Client();
public:
	
	static Client * GetInstance();
	~Client();
	bool initClient();
	bool connectClient();
	bool sendData();
	bool recvData();

	bool closeClient();
	bool cleanUpClient();
	void Reset();
	int getTeam();
	int Extras();

};
#endif // !_CLIENT_H_
