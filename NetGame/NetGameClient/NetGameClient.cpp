#define _WINSOCK_DEPRECATED_NO_WARNINGS 
//
#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <conio.h>
//
#include <iostream>
#include <map>
//
#include "MessagePacket.h"
#include "PlayerData.h"
//
#pragma comment(lib, "WS2_32.lib")
//
std::map<SOCKET, PlayerData*> G_PlayerList;
SOCKET MySocketID = 0L;
CRITICAL_SECTION G_CSPlayerList;
bool G_ProgramRunning = true;
//
void ProcessPacket(char* data)
{
	unsigned short Code = 0;
	memcpy(&Code, &data[0], sizeof(Code));
	Code = ntohs(Code);

	SOCKET FromID = 0;
	memcpy(&FromID, &data[2], sizeof(FromID));
	FromID = ntohll(FromID);

	switch ((MessagePacket)Code)
	{
		case MessagePacket::S2C_RegisterID:
		{
			std::cout << "MessagePacket::S2C_RegisterID" << std::endl;
			PlayerData* NewPlayer = new PlayerData();
			NewPlayer->mSocket = FromID;
			MySocketID = FromID;
			G_PlayerList[FromID] = NewPlayer;
			break;
		}
		case MessagePacket::S2C_Spawn:
		{
			std::cout << "MessagePacket::S2C_Spawn" << std::endl;
			PlayerData* NewPlayer = new PlayerData();
			NewPlayer->mSocket = FromID;
			G_PlayerList[FromID] = NewPlayer;
			break;
		}
		case MessagePacket::S2C_Destroy:
		{
			std::cout << "MessagePacket::S2C_Destroy" << std::endl;
			G_PlayerList.erase(G_PlayerList.find(FromID));
			break;
		}
		case MessagePacket::S2C_Move:
		{
			int X = 0;
			memcpy(&X, &data[10], sizeof(X));
			X = ntohl(X);

			int Y = 0;
			memcpy(&Y, &data[14], sizeof(Y));
			Y = ntohl(Y);

			auto UpdatePlayer = G_PlayerList.find(FromID);
			UpdatePlayer->second->mPosX = X;
			UpdatePlayer->second->mPosY = Y;

			std::cout << "PlayerID" << FromID << ", X :" << X << ", Y :" << Y << std::endl;

			break;
		}
		default:
		{
			std::cout << "Not Found Code." << std::endl;
			break;
		}
	}
}

unsigned WINAPI TWorker_Read(void* Arg)
{
	SOCKET ServerSocket = *(SOCKET*)Arg;
	char Data[18] = { 0, };
	while (true)
	{
		memset(&Data, 0, sizeof(Data));
		int RecvBytes = recv(ServerSocket, Data, sizeof(Data), 0);
		if (RecvBytes <= 0)
		{
			break;
		}
		ProcessPacket(&Data[0]);
	}
	closesocket(ServerSocket);
	return 0;
}


unsigned WINAPI TWorker_Write(void* Arg)
{
    SOCKET ServerSocket = *(SOCKET*)Arg;
    while (true)
    {
        int KeyCode = _getch();
        std::map<SOCKET, PlayerData*>::iterator MyPlayer = G_PlayerList.find(MySocketID);
        switch (KeyCode)
        {
			case 'q':
			case 'Q':
			{ G_ProgramRunning = false; break; }
            case 'w':
            case 'W':
            { MyPlayer->second->mPosY--; break; }
            case 's':
            case 'S':
            { MyPlayer->second->mPosY++; break; }
            case 'a':
            case 'A':
            { MyPlayer->second->mPosX--; break; }
            case 'd':
            case 'D':
            { MyPlayer->second->mPosX++; break; }
        }
        char Data[18] = { 0, };
        unsigned short Code = htons((unsigned short)MessagePacket::C2S_Move);
        memcpy(&Data[0], &Code, sizeof(Code));
        SOCKET SendID = htonll(MyPlayer->second->mSocket);
        memcpy(&Data[2], &SendID, sizeof(SendID));
        int posX = htonl(MyPlayer->second->mPosX);
        memcpy(&Data[10], &posX, sizeof(posX));
        int posY = htonl(MyPlayer->second->mPosY);
        memcpy(&Data[14], &posY, sizeof(posY));
        int SendBytes = send(ServerSocket, Data, sizeof(Data), 0);
		if (SendBytes <= 0)
		{
			break;
		}
    }
	closesocket(ServerSocket);
	return 0;
}

int main(int argc, char* argv[])
{
	InitializeCriticalSection(&G_CSPlayerList);
	WSAData wsaData = {0,};
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { exit(-1); }

	SOCKADDR_IN ServerSocketAddr = { 0, };
	ServerSocketAddr.sin_family = PF_INET;
	ServerSocketAddr.sin_port = htons(4949);
	ServerSocketAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	SOCKET ServerSocket = NULL;
	HANDLE h1 = NULL;
	HANDLE h2 = NULL;
	while (G_ProgramRunning)
	{
		if (ServerSocket != NULL) { closesocket(ServerSocket); ServerSocket = NULL; }
		ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (ServerSocket == INVALID_SOCKET) { continue; }
		if (connect(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr)) != 0) { continue; };
		if (h1 != NULL) { CloseHandle(h1); h1 = NULL; }
		if (h2 != NULL) { CloseHandle(h2); h2 = NULL; }
		h1 = (HANDLE)_beginthreadex(nullptr, 0, TWorker_Read, (void*)&ServerSocket, 0, nullptr);
		h2 = (HANDLE)_beginthreadex(nullptr, 0, TWorker_Write, (void*)&ServerSocket, 0, nullptr);
		WaitForSingleObject(h1, INFINITE);
		WaitForSingleObject(h2, INFINITE);
	}
	if (ServerSocket != NULL) { closesocket(ServerSocket); ServerSocket = NULL; }
	if (h1 != NULL) { CloseHandle(h1); h1 = NULL; }
	if (h2 != NULL) { CloseHandle(h2); h2 = NULL; }
	WSACleanup();
	DeleteCriticalSection(&G_CSPlayerList);
}