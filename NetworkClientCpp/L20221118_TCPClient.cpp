#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <timeapi.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma comment(lib, "WS2_32.lib")

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

using namespace std;

unsigned WINAPI WorkThread(void* args)
{
	SOCKET TCPClientSocket = *(SOCKET*)args;
	while (true)
	{
		char Buffer[PACKET_SIZE] = { 0, };
		int RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
		if (RecvBytes <= 0)
		{
			break;
		}
		cout << "[Server] : " << Buffer << endl;
	}
	return 0;
}

//int L20221118_TCPClient_main(int argc, char* argv[])
int main(int argc, char* argv[])
{
	HANDLE WorkHandle = nullptr;
	WSAData wsadata = { 0, };
	SOCKET TCPClientSocket = NULL;
	SOCKADDR_IN TCPServerAddress = { 0, };
	int Retval = 0;

	//1.Load Winsock2.2
	Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (Retval != 0)
	{
		cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
		exit(-1);
	}
	cout << "[SYS]Winsock 2.2 Load Complete!" << endl;
	
	//3.Connect to TCPServer
	TCPServerAddress.sin_family = PF_INET;
	TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
	TCPServerAddress.sin_port = htons(SERVER_PORT);

	int SendBytes = 0;
	int RecvBytes = 0;
	char Buffer[PACKET_SIZE] = { 0, };
	bool bShowOnce = false;

	while (true)
	{
		if (!bShowOnce)
		{ 
			cout << "[ERR]TCPSocket Connecting...";
			bShowOnce = true; 
		}
		if (TCPClientSocket) { closesocket(TCPClientSocket);  }
		TCPClientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (TCPClientSocket == INVALID_SOCKET)
		{
			continue;
		}
		Retval = connect(TCPClientSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
		if (Retval == SOCKET_ERROR)
		{
			continue;
		}
		cout << "OK!" << endl;
		cout << "[Chatting Started]" << endl;
		if (WorkHandle) 
		{ 
			WaitForSingleObject(WorkHandle, INFINITE);
			CloseHandle(WorkHandle); 
		}
		WorkHandle = (HANDLE)_beginthreadex(nullptr, 0, WorkThread, (void*)&TCPClientSocket, 0, nullptr);

		while (true)
		{
			memset(Buffer, 0, sizeof(Buffer));
			string strMessage = "";
			getline(cin, strMessage);
			strcpy(Buffer, strMessage.c_str());
			SendBytes = send(TCPClientSocket, Buffer, (int)strlen(Buffer), 0);
			if (SendBytes <= 0)
			{
				break;
			}
		}
		cout << "[Chatting Finished]" << endl;
		bShowOnce = false;
	}
	if (TCPClientSocket) { closesocket(TCPClientSocket); }
	WSACleanup();
	return 0;
}