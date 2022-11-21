/*---------------------------------------------------------------
    TCP Echo Server v2
    -- TCPŬ���̾�Ʈ�� NTS(Null Terminated String)�� ������, �������� �޾Ƽ� �״�� �ǵ����ش�.
    -- Ŭ���̾�Ʈ�� ������ ������ �� �翬��õ��� �Ѵ�.
    -- ���� �޽����� �޽��� ���/�޽��� �ٵ�� �������Ͽ� �ǵ����ְ�, ť�� �����Ѵ�.

    �� 2022.11.20 TODO
    -- Ŭ�� & ������ �޽����� �ְ���� ��, �޽��� ���/�޽��� �ٵ� ����� �ؼ��Ѵ�.
    -- ������ Recv���� Message Queue�� �����, Network Recv Thread���� RecvQueue Enqueue,
       RecvQueue Thread���� RecvQueue Dequeue�Ͽ� �޽����� �ؼ��Ѵ�.
    -- ������ MainThread���� Input�� �޾�, SendQueue Enqueue, SendQueue Thread���� Network Send����.

       MainThread : ������Է�
       NetworkRecvThread : RecvQueue�� �о ������� ó��
       NetworkSendThread : SendQueue�� �о ������� Network Send
       ProcessRecvQueueThread : Network Recv ó��

---------------------------------------------------------------*/
/*
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//CHeader
#include <WinSock2.h>
//CppHeader
#include <iostream>
#include <queue>
//CustomHeader

//Library
#pragma comment(lib, "WS2_32.lib")

//define
#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

using namespace std;

enum class MessageID : unsigned int
{
    Undefined = 0,
    NullTerminatedString = 1,
};

struct MsgHeader
{
    unsigned int MsgID;   //�޽����� ID
    unsigned int MsgSize; //�޽��� ��� ũ�⸦ ������ �޽����� ��ü ����
};

struct MsgNullTerminatedString
{
    MsgHeader MsgHead;
    char* MsgNTS;
    int MsgLen;

    MsgNullTerminatedString(char* InMsgNTS, int InMsgLen)
    {
        MsgHead.MsgID = (unsigned int)MessageID::NullTerminatedString;
        MsgLen = InMsgLen + 1;
        MsgNTS = new char[MsgLen];
        memcpy(MsgNTS, InMsgNTS, MsgLen);
        MsgHead.MsgSize = sizeof(MsgHead) + sizeof(MsgLen) + MsgLen;
    }
    ~MsgNullTerminatedString()
    {
        delete[] MsgNTS;
    }
};

int H20221120_TCPServer4_main(int argc, char* argv[])
{
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;

    //1. Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR] Winsock2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS] Winsock2.2 Load Success!" << endl;

    //2. Create TCPServerSocket
    TCPServerAddress.sin_family = AF_INET;
    //inet_addr : add define _WINSOCK_DEPRECATED_NO_WARNINGS
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    TCPServerAddress.sin_port = htons(SERVER_PORT);

    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR] TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS] TCPSocket Creation Complete!" << endl;

    //3. Bind TCPServerSocket to Address
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR] TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS] TCPSocket Address Bind Complete!" << endl;

    //4. Set TCPServerSocket Listen State
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR] TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS] TCPServer Network Started." << endl;

    bool bShowMessageOnce = false;
    while (true)
    {
        if (!bShowMessageOnce) { cout << "[SYS] TCPClient Connecting..."; bShowMessageOnce = true; }
        SOCKADDR_IN TCPClientAddress = { 0, };
        int szTCPClientAddress = sizeof(TCPClientAddress);
        SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
        if (TCPClientSocket == INVALID_SOCKET)
        {
            continue;
        }
        cout << "OK." << endl;
        cout << "[SYS] TCPClientSocket Network Started." << endl;
        queue<void*> RecvQueue;
        while (true)
        {
            int SendBytes = 0;
            int RecvBytes = 0;
            char Buffer[PACKET_SIZE] = { 0, };
            //In Order to Make NTS(Null Terminated String), Add - 1('\0')
            RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer) - 1, 0);
            if (RecvBytes == 0)
            {
                cout << "[SYS] TCPClientSocket Network Finished." << endl;
                break;
            }
            else if (RecvBytes < 0)
            {
                cout << "[ERR] TCPClientSocket Error Occured! ErrorCode : " << GetLastError() << endl;
                break;
            }

            MsgNullTerminatedString* msg = new MsgNullTerminatedString(Buffer, (int)strlen(Buffer));
            RecvQueue.push(msg);
            cout << "[SYS] RECV Message : " << msg->MsgNTS << endl;
            //In Order to Make NTS(Null Terminated String), Add + 1 ('\0')
            SendBytes = send(TCPClientSocket, msg->MsgNTS, msg->MsgLen, 0);
            if (SendBytes == 0)
            {
                cout << "[SYS] TCPClientSocket Network Finished." << endl;
                break;
            }
            else if (SendBytes < 0)
            {
                cout << "[ERR] TCPClientSocket Error Occured! ErrorCode : " << GetLastError() << endl;
                break;
            }
        }
        while (!RecvQueue.empty())
        {
            MsgHeader* ptr = (MsgHeader*)RecvQueue.front();
            switch (ptr->MsgID)
            {
                case (unsigned int)MessageID::NullTerminatedString:
                {
                    MsgNullTerminatedString* msg = (MsgNullTerminatedString*)ptr;
                    cout << "[SYS] Queue RECV Message : " << msg->MsgNTS << endl;
                    delete(msg);
                }
            }
            RecvQueue.pop();
        }
        if (TCPClientSocket) { closesocket(TCPClientSocket); }
        bShowMessageOnce = false;
    }
    if (TCPServerSocket) { closesocket(TCPServerSocket); }
    WSACleanup();
    cout << "[SYS] TCPServer Network Finished." << endl;
    return 0;
}
*/