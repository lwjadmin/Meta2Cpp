#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "0.0.0.0" /*"127.0.0.1"*/
#define SERVER_PORT 5001
#define PACKET_SIZE 1024

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

enum class EMsgID : unsigned short
{
    Unknown = 0,
    NullTerminatedString = 1,
    TwoNumbers = 2,
};

struct TMsgHeader
{
    unsigned short MsgID;
    unsigned short MsgLength;
};

struct TMsgNts
{
    TMsgHeader MsgHead;
    char Message[PACKET_SIZE];

    TMsgNts(TMsgHeader* InMsgHead)
    {
        MsgHead = *InMsgHead;
        memset(Message, 0, sizeof(Message));
    }
    unsigned short GetMsgLength()
    {
        return MsgHead.MsgLength - sizeof(TMsgHeader);
    }
    void Serialize(const char* str, size_t strlen)
    {
        MsgHead.MsgID = (unsigned short)EMsgID::NullTerminatedString;
        MsgHead.MsgLength = (strlen + 1) + (unsigned short)sizeof(TMsgHeader);
        memcpy(Message, str, strlen + 1);
    }
    void DeSerialize()
    {
        //do Nothing!
    }
};

struct TMsgTwoNumbers
{
    TMsgHeader MsgHead;
    int Number1;
    int Number2;

    TMsgTwoNumbers()
    {
        MsgHead.MsgID = (unsigned short)EMsgID::TwoNumbers;
        MsgHead.MsgLength = sizeof(TMsgTwoNumbers);
        Number1 = 0;
        Number2 = 0;
    }
    TMsgTwoNumbers(TMsgHeader* InMsgHead)
    {
        MsgHead = *InMsgHead;
        Number1 = 0;
        Number2 = 0;
    }
    unsigned short GetMsgLength()
    {
        return MsgHead.MsgLength - sizeof(TMsgHeader);
    }
    void Serialize()
    {
        Number1 = htonl(Number1);
        Number2 = htonl(Number2);
    }
    void DeSerialize()
    {
        Number1 = ntohl(Number1);
        Number2 = ntohl(Number2);
    }
};

int L20221108_TCPServer_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    bool bExitCalled = false;
    bool bConnectionSuccess = false;
    WSADATA WSAData = { 0, };
    SOCKET ServerSocket = NULL;
    SOCKET ClientSocket = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    SOCKADDR_IN ClientAddress = { 0, };
    char Buffer[PACKET_SIZE] = { 0, };
    int Result = 0;

    //--Init WinSock 2.2------------------------------------------------------
    //������ 2.2 �ʱ�ȭ
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        cout << "[ERR]WinSock2.2 Init Error! ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    //--Set ServerAddress & ServerSocket---------------------------------------
    //���� ����
    ServerAddress.sin_family = PF_INET/*AF_INET*/;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);
    ServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (ServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]ServerSocket Creation Error! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    //--Bind ServerSocket & Address---------------------------------------------
    //���Ͽ� IP�ּ�, ��Ʈ ���ε�
    Result = bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Bind Error! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    //--ServerSocket Listen------------------------------------------------------
    //���� �б��غ�...(�ٸ� ������ Connect�õ��� �ϴ��� �Ĵٺ���.)
    /*------------------------------------------------------------------------------
    listen : 1~100�� ������ ������ ó���� �� listen�� �Ѵ�.
    BackLog : �� �ǹ̾���. 0���� �ʱ�ȭ
    ------------------------------------------------------------------------------*/
    Result = listen(ServerSocket, 0/*SOMAXCONN*/);
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Listen Error! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    do
    {
        if (!bConnectionSuccess)
        {
            cout << "[SYS]Waiting For TCPClient(Blocking)...";
            //�ٸ� ������ Connect�õ��ϴ°��� �޾Ƶ鿩�� ��ûIP,��Ʈ�� ����Ѵ�. (TCPClient �� Send/Recv �뵵) 
            //Accept : ���ŷó���� (�ٸ� ������ ���ö����� ��ٸ�...)  
            //�񵿱� Accept/�ȶ��� Accept : IOCP / EPoll
            if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
            int szClientAddress = sizeof(ClientAddress);
            ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddress, &szClientAddress);
            if (ClientSocket == INVALID_SOCKET)
            {
                cout << "\n[ERR]ClientSocket Accept Error! ErrorCode : " << GetLastError() << endl;
                continue;
            }
            else
            {
                cout << "Connected!" << endl;
                bConnectionSuccess = true;
            }
        }
        int SendBytes = 0;
        int RecvBytes = 0;
        TMsgHeader MsgHead = { 0, };
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        RecvBytes = recv(ClientSocket, (char*)&MsgHead, sizeof(MsgHead), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]Server Recv Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        switch (MsgHead.MsgID)
        {
            case (unsigned short)EMsgID::NullTerminatedString:
            {
                TMsgNts MsgBody(&MsgHead);
                cout << "OK!\n[SYS]Message Type : EMsgID::NullTerminatedString" << endl;
                RecvBytes = recv(ClientSocket, (char*)&MsgBody + sizeof(MsgHead), MsgBody.GetMsgLength(), 0);
                MsgBody.DeSerialize();
                cout << "[SYS]Server Received Message : " << MsgBody.Message << endl;
                //--RE-SEND---------------------------------------------------------------------
                SendBytes = send(ClientSocket, (char*)&MsgBody, MsgBody.MsgHead.MsgLength, 0);
                if (SendBytes <= 0)
                {
                    cout << "[ERR]Server Send Error! ErrorCode : " << GetLastError() << endl;
                    bConnectionSuccess = false;
                    continue;
                }
                else
                {
                    cout << "[SYS]Server Send Message ByteCount : " << SendBytes << endl;
                }
                break;
            }
            case (unsigned short)EMsgID::TwoNumbers:
            {
                TMsgTwoNumbers MsgBody(&MsgHead);
                cout << "OK!\n[SYS]Message Type : EMsgID::TwoNumbers" << endl;
                RecvBytes = recv(ClientSocket, (char*)&MsgBody + sizeof(MsgHead), MsgBody.GetMsgLength(), 0);
                MsgBody.DeSerialize();
                cout << "[SYS]Server Received Number1 : " << MsgBody.Number1 << endl;
                cout << "[SYS]Server Received Number2 : " << MsgBody.Number2 << endl;
                break;
            }
        }

    } while (!bExitCalled);

    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    if (ServerSocket) { closesocket(ServerSocket); ServerSocket = NULL; }
    WSACleanup();
    return 0;
}
