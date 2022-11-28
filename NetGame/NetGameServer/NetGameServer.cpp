#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
//
#include "MessagePacket.h"
#include "PlayerData.h"
//
using namespace std;
//
#pragma comment(lib, "WS2_32.lib")
//
/*-------------------------------------
    2    8         4  4
    Code SOCKET_ID X  Y
    0    2         10 14
-------------------------------------*/
char Data[18] = { 0, };
map<SOCKET, PlayerData*> PlayerList;

int main(int argc, char* argv[])
{
    WSAData WSAdata = { 0, };
    if (WSAStartup(MAKEWORD(2, 2), &WSAdata) != 0) 
    {
        cout << "[ERR] WSAStartup Error Occured! ErrorCode : " << GetLastError() << endl; exit(-1);
    }
    SOCKET ListenSocket = NULL;
    if ((ListenSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) 
    { 
        cout << "[ERR] ListenSocket Creation Error Occured! ErrorCode : " << GetLastError() << endl; exit(-2);
    }
    SOCKADDR_IN ListenSocketAddr = { 0, };
    ListenSocketAddr.sin_family = PF_INET;
    ListenSocketAddr.sin_port = htons(4949);
    ListenSocketAddr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
    if (bind(ListenSocket, (SOCKADDR*)&ListenSocketAddr, sizeof(ListenSocketAddr)) == SOCKET_ERROR) 
    { 
        cout << "[ERR] ListenSocket Bind Error Occured! ErrorCode : " << GetLastError() << endl; exit(-3);
    };
    if (listen(ListenSocket, 0) == SOCKET_ERROR) 
    {
        cout << "[ERR] ListenSocket Listen Error Occured! ErrorCode : " << GetLastError() << endl; exit(-4);
    };
    cout << "[SYS] TCP Server Socket Listening..." << endl;
    
    fd_set reads; 
    FD_ZERO(&reads);
    //SOCKET 구조체 배열(복사본) 할당
    fd_set copys; 
    FD_ZERO(&copys);
    //ListenSocket의 상태를 감시하여 OS에 전달할 수 있는 구조체를 할당 
    FD_SET(ListenSocket, &reads);
    //1초마다 한번씩 감시
    TIMEVAL Timeout;
    Timeout.tv_sec = 1; //초(0~N)
    Timeout.tv_usec = 0; //밀리초(0~999)

    while (true)
    {
        
        copys = reads;
        //Timeout마다 소켓상태가 바뀐 것이 있는지 확인(Socket Read Select)
        int fd_num = select(0, &copys, 0, 0, &Timeout);
        if (fd_num == SOCKET_ERROR)
        {
            //소켓 에러가 발생할 경우
            cout << "[ERR] ListenSocket select Error Occured! ErrorCode : " << GetLastError() << endl; exit(-5);
        }
        else if (fd_num == 0)
        {
            //바뀐 것이 없다면, Continue
            continue;
        }

        for (int i = 0; i < (int)reads.fd_count; i++)
        {
            //해당 소켓이 바뀐게 있을 경우
            if (FD_ISSET(reads.fd_array[i], &copys)) 
            {
                //바뀐게 있으면, 자신(리슨소켓)도 바뀌었다고 알림이 들어온다!
                //리슨소켓에서 클라 소켓 Connect를 Accpet하고 reads에 추가
                if (reads.fd_array[i] == ListenSocket)
                {
                    //1.Accept
                    sockaddr_in TCPClientAddress = { 0, };
                    int szTCPClientAddress = sizeof(TCPClientAddress);
                    SOCKET NewClientSocket = accept(ListenSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
                    FD_SET(NewClientSocket, &reads);
                    cout << "[SYS] New TCPClient["<< NewClientSocket <<"] Connected."<<endl;

                    //2.Add PlayerList
                    PlayerData* NewPlayer = new PlayerData();
                    NewPlayer->MySocket = NewClientSocket;
                    //PointXY = 0,0
                    PlayerList[NewClientSocket] = NewPlayer;

                    //3.1 Server->NewClient Send S2C_RegisterID
                    unsigned short Code = htons((unsigned short)MessagePacket::S2C_RegisterID);
                    memcpy(&Data[0], &Code, sizeof(Code));
                    SOCKET SendID = htonll(NewClientSocket);
                    memcpy(&Data[2], &SendID, sizeof(SendID));
                    int SentBytes = 0;
                    int TotalSentBytes = 0;
                    do
                    {
                        SentBytes = send(NewClientSocket, &Data[TotalSentBytes], sizeof(Data) - TotalSentBytes, 0);
                        if (SentBytes < 0) { break; } //Recv단에서 연결체크 & Disconnect하기 때문에, OnSendConnectionClosed 체크X
                        TotalSentBytes += SentBytes;
                    } while (TotalSentBytes < sizeof(Data));

                    //3.2 Server->OldClient S2C_Spawn : 신규 접속한 클라 정보를 기존 클라에게 전달
                    for (auto Player : PlayerList)
                    {
                        //S2C_Spawn
                        if (Player.first != NewClientSocket)
                        {
                            unsigned short Code = htons((unsigned short)MessagePacket::S2C_Spawn);
                            memcpy(&Data[0], &Code, sizeof(Code));
                            SOCKET SpawnID = htonll(NewClientSocket);
                            memcpy(&Data[2], &SpawnID, sizeof(SpawnID));
                            int X = ntohl(0);
                            memcpy(&Data[10], &X, sizeof(X));
                            int Y = ntohl(0);
                            memcpy(&Data[14], &Y, sizeof(Y));
                            int SentBytes = 0;
                            int TotalSentBytes = 0;
                            do
                            {
                                SentBytes = send(Player.second->MySocket, &Data[TotalSentBytes], sizeof(Data) - TotalSentBytes, 0);
                                if (SentBytes < 0) { break; } //Recv단에서 연결체크 & Disconnect하기 때문에, OnSendConnectionClosed 체크X
                                TotalSentBytes += SentBytes;
                            } while (TotalSentBytes < sizeof(Data));
                        }
                    }

                    //3.3 Server->NewClient S2C_Spawn : 신규 접속한 클라에게 기존 클라 정보 전달
                    for (auto Player : PlayerList)
                    {
                        if (Player.first != NewClientSocket)
                        {
                            //S2C_Spawn
                            unsigned short Code = htons((unsigned short)MessagePacket::S2C_Spawn);
                            memcpy(&Data[0], &Code, sizeof(Code));
                            SOCKET SpawnID = htonll(Player.second->MySocket);
                            memcpy(&Data[2], &SpawnID, sizeof(SpawnID));
                            int X = ntohl(Player.second->X);
                            memcpy(&Data[10], &X, sizeof(X));
                            int Y = ntohl(Player.second->Y);
                            memcpy(&Data[14], &Y, sizeof(Y));
                            int SentBytes = 0;
                            int TotalSentBytes = 0;
                            do
                            {
                                SentBytes = send(NewClientSocket, &Data[TotalSentBytes], sizeof(Data) - TotalSentBytes, 0);
                                if (SentBytes < 0) { break; } //Recv단에서 연결체크 & Disconnect하기 때문에, OnSendConnectionClosed 체크X
                                TotalSentBytes += SentBytes;
                            } while (TotalSentBytes < sizeof(Data));
                        }
                    }
                }
                else
                {
                    SOCKET ClientSocket = reads.fd_array[i];
                    int RecvBytes = 0;
                    int TotalRecvBytes = 0;
                    do
                    {
                        RecvBytes = recv(ClientSocket, &Data[TotalRecvBytes], sizeof(Data) - TotalRecvBytes, 0);
                        if (RecvBytes <= 0) { break; }
                        TotalRecvBytes += RecvBytes;
                    } while (TotalRecvBytes < sizeof(Data));

                    if (RecvBytes <= 0)
                    {
                        //OnRecv Failed, [1]Disconnect
                        cout << "[SYS] TCPClient[" << ClientSocket << "] Disconnected." << endl;
                        closesocket(ClientSocket);
                        FD_CLR(ClientSocket, &reads);
                        PlayerList.erase(PlayerList.find(ClientSocket));

                        for (auto Player : PlayerList)
                        {
                            unsigned short Code = htons((unsigned short)MessagePacket::S2C_Destroy);
                            memcpy(&Data[0], &Code, sizeof(Code));
                            SOCKET SendID = htonll(ClientSocket);
                            memcpy(&Data[2], &SendID, sizeof(SendID));
                            int SentBytes = 0;
                            int TotalSentBytes = 0;
                            do
                            {
                                SentBytes = send(Player.second->MySocket, &Data[TotalSentBytes], sizeof(Data) - TotalSentBytes, 0);
                                TotalSentBytes += SentBytes;
                            } while (TotalSentBytes < sizeof(Data));
                        }
                        break;
                    }
                    else
                    {
                        //OnRecv Success, Process Recv Message 
                        unsigned short Code = 0;
                        memcpy(&Code, &Data[0], sizeof(Code));
                        SOCKET FromID = 0;
                        memcpy(&FromID, &Data[2], sizeof(FromID));
                        Code = ntohs(Code);
                        FromID = ntohll(FromID);
                        int X = 0;
                        int Y = 0;

                        //메시지 처리
                        switch ((MessagePacket)Code)
                        {
                            case MessagePacket::C2S_Move:
                            {
                                memcpy(&X, &Data[10], sizeof(X));
                                X = ntohl(X);
                                memcpy(&Y, &Data[14], sizeof(Y));
                                Y = ntohl(Y);
                                //1. 플레이어 이동정보 갱신
                                auto UpdatePlayer = PlayerList.find(FromID);
                                UpdatePlayer->second->X = X;
                                UpdatePlayer->second->Y = Y;

                                //2. 모든 클라이언트들에게 이동정보를 전송!
                                unsigned short Code = htons((unsigned short)MessagePacket::S2C_Move);
                                memcpy(&Data[0], &Code, sizeof(Code));
                                SOCKET SendID = htonll(FromID);
                                memcpy(&Data[2], &SendID, sizeof(SendID));
                                int Temp = htonl(X);
                                memcpy(&Data[10], &Temp, sizeof(Temp));
                                Temp = htonl(Y);
                                memcpy(&Data[14], &Temp, sizeof(Temp));

                                for (auto Player : PlayerList)
                                {
                                    int SentBytes = 0;
                                    int TotalSentBytes = 0;
                                    do
                                    {
                                        SentBytes = send(Player.second->MySocket, &Data[TotalSentBytes], sizeof(Data) - TotalSentBytes, 0);
                                        TotalSentBytes += SentBytes;
                                    } while (TotalSentBytes < sizeof(Data));
                                }
                                break;
                            }
                            default:
                            {
                                cout << "[ERR] Wrong Message Received!" << endl;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    closesocket(ListenSocket);
    //DeleteCriticalSection(&CSPlayerList);
    WSACleanup();
}