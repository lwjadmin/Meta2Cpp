/*---------------------------------------------------------------
    TCP Echo Server v2
    -- TCP클라이언트가 NTS(Null Terminated String)를 보내면, 서버에서 받아서 그대로 되돌려준다.
    -- 클라이언트가 연결이 끊겼을 때 재연결시도를 한다.
    -- 받은 메시지를 메시지 헤더/메시지 바디로 재정리하여 되돌려주고, 큐에 저장한다.

    ※ 2022.11.20 TODO
    -- 클라 & 서버간 메시지를 주고받을 때, 메시지 헤더/메시지 바디를 만들어 해석한다.
    -- 서버의 Recv단을 Message Queue로 만들어, Network Recv Thread에서 RecvQueue Enqueue,
       RecvQueue Thread에서 RecvQueue Dequeue하여 메시지를 해석한다.
    -- 서버의 MainThread에서 Input을 받아, SendQueue Enqueue, SendQueue Thread에서 Network Send하자.

       MainThread : 사용자입력
       NetworkRecvThread : RecvQueue를 읽어서 있을경우 처리
       NetworkSendThread : SendQueue를 읽어서 있을경우 Network Send
       ProcessRecvQueueThread : Network Recv 처리

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
    unsigned int MsgID;   //메시지의 ID
    unsigned int MsgSize; //메시지 헤더 크기를 포함한 메시지의 전체 길이
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