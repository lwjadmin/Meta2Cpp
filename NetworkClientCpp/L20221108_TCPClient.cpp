#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "127.0.0.1"
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

    TMsgNts()
    {
        MsgHead.MsgID = (unsigned short)EMsgID::NullTerminatedString;
        MsgHead.MsgLength = sizeof(TMsgNts);
        memset(Message, 0, sizeof(Message));
    }

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
        MsgHead.MsgLength = ((unsigned short)strlen + 1) + (unsigned short)sizeof(TMsgHeader);
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

int L20221108_TCPClient_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    bool bExitCalled = false;
    bool bConnectionSuccess = false;
    WSADATA WSAData = { 0, };
    SOCKET ClientSocket = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    std::string Message = "";
    int Result = 0;

    //--Init WinSock 2.2------------------------------------------------------------
    //윈소켓2.2를 쓸 준비를 한다.
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        std::cout << "[ERR]WinSock2.2 Init Error! ErrorCode : " << GetLastError() << std::endl;
        exit(-1);
    }
    //--Set ServerAddress-----------------------------------------------------------
    //연결할 TCP서버의 주소와 포트를 지정한다. 
    ServerAddress.sin_family = PF_INET/*AF_INET*/;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT); //Host to Network : short Little Endian에서 short Big Endian으로 변환
    do
    {
        //--Wait for Server Connection-----------------------------------------------
        if (!bConnectionSuccess)
        {
            std::cout << "[SYS]TCPClient Try to Connect TCPServer...";
            //연결이 실패할 경우, 소켓을 닫고 다시 만들기 위해서 해당 구문 추가
            if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
            //TCP소켓을 만든다. 
            ClientSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
            if (ClientSocket == INVALID_SOCKET)
            {
                std::cout << "\n[ERR]ClientSocket Creation Error! ErrorCode : " << GetLastError() << std::endl;
                continue;
            }
            //TCP서버와의 연결을 시도한다. 
            Result = connect(ClientSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
            if (Result == SOCKET_ERROR)
            {
                std::cout << "\n[ERR]ClientSocket Connection Failed! ErrorCode : " << GetLastError() << std::endl;
                continue;
            }
            else
            {
                std::cout << "Connected!" << std::endl;
                bConnectionSuccess = true;
            }
        }

        int SendBytes = 0;
        int RecvBytes = 0;
        
        //--CASE 1---------------------------------------------------------------------
        /*
        std::cout << "[SYS]Input Send Message : ";
        std::getline(std::cin, Message);
        TMsgNts SendMsg;
        SendMsg.Serialize(Message.c_str(), Message.size());
        SendBytes = send(ClientSocket, (char*)&SendMsg, SendMsg.MsgHead.MsgLength, 0);
        if (SendBytes <= 0)
        {
            std::cout << "[ERR]Client Send Error! ErrorCode : " << GetLastError() << std::endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            std::cout << "[SYS]Client Send Message ByteCount : " << SendBytes <<std::endl;

            //--RECV---------------------------------------------------------------------
            std::cout << "[SYS]Waiting For Message...";
            TMsgHeader MsgHead;
            RecvBytes = recv(ClientSocket, (char*)&MsgHead, sizeof(MsgHead), 0);
            if (RecvBytes <= 0)
            {
                std::cout << "\n[ERR]Client Recv Error : " << GetLastError() << std::endl;
                bConnectionSuccess = false;
                continue;
            }
            switch (MsgHead.MsgID)
            {
                case (unsigned short)EMsgID::NullTerminatedString:
                {
                    TMsgNts MsgBody(&MsgHead);
                    std::cout << "OK!\n[SYS]Message Type : EMsgID::NullTerminatedString" << std::endl;
                    RecvBytes = recv(ClientSocket, (char*)&MsgBody + sizeof(MsgHead), MsgBody.GetMsgLength(), 0);
                    MsgBody.DeSerialize();
                    std::cout << "[SYS]Client Received Message : " << MsgBody.Message << std::endl;
                    break;
                }
                default:
                {
                    std::cout << "Undefined Message. GoodBye." << std::endl;
                }
            }//eoswitch
        }
        */
        //--CASE 2------------------------------------------------------------------------
        std::cout << "[SYS]Input Send Two Numbers : ";
        TMsgTwoNumbers SendMsg;
        cin >> SendMsg.Number1 >> SendMsg.Number2;
        SendMsg.Serialize();
        SendBytes = send(ClientSocket, (char*)&SendMsg, SendMsg.MsgHead.MsgLength, 0);
        if (SendBytes > 0)
        { 
            std::cout << "[SYS]Client Send Message ByteCount : " << SendBytes << std::endl;
        }
        
#pragma endregion
    } while (!bExitCalled);
    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    WSACleanup();
    return 0;
}
