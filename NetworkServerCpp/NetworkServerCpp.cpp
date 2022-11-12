#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "0.0.0.0" /*"127.0.0.1"*/
#define SERVER_PORT 5001
#define PACKET_SIZE 1024
 
struct MessagePack
{
    int NumA;
    int NumB;
};

int GetFileSizeBytes(const char* filename)
{
    int size = 0;
    FILE* fp = fopen(filename, "rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fclose(fp);
    }
    return size;
}

int NetworkServerCpp_main(int argc, char* argv[])
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
    //윈소켓 2.2 초기화
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        cout << "[ERR]WinSock2.2 Init Error! ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    //--Set ServerAddress & ServerSocket---------------------------------------
    //소켓 생성
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);
    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]ServerSocket Creation Error! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    //--Bind ServerSocket & Address---------------------------------------------
    //소켓에 IP주소, 포트 바인딩
    Result = bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
    if (Result == SOCKET_ERROR)
    {
        cout << "[ERR]ServerSocket Bind Error! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    //--ServerSocket Listen------------------------------------------------------
    //소켓 읽기준비...(다른 소켓이 Connect시도를 하는지 쳐다본다.)
    /*------------------------------------------------------------------------------
    listen : 1~100명 내외의 연결을 처리할 때 listen을 한다.
    BackLog : 별 의미없다. 0으로 초기화
    ------------------------------------------------------------------------------*/
    Result = listen(ServerSocket, SOMAXCONN);
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
            //다른 소켓이 Connect시도하는것을 받아들여서 요청IP,포트를 기록한다. (TCPClient 간 Send/Recv 용도) 
            //Accept : 블로킹처리됨 (다른 소켓이 들어올때까지 기다림...)  
            //비동기 Accept/똑똑한 Accept : IOCP / EPoll
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
#pragma  region --EXAM_01-------------------------------------------------------------------------
        /*
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]Server Recv Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        cout << "Received!" << endl;
        cout << "[SYS]Received Message : " << Buffer << endl;
        if (Buffer[0] == 'K' && Buffer[1] == 'I' && Buffer[2] == 'L' && Buffer[3] == 'L')
        {
            bExitCalled = true;
            break;
        }
        //--SEND---------------------------------------------------------------------
        int SendBytes = send(ClientSocket, Buffer, strlen(Buffer), 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]Server Send Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            cout << "[SYS]Server Send Message : " << Buffer << endl;
        }
        */
#pragma  endregion
#pragma  region --EXAM_02-------------------------------------------------------------------------
        /*
        //--SEND---------------------------------------------------------------------
        memset(Buffer, 0, PACKET_SIZE);
        cout << "[SYS]Server Send Message : ";
        getline(cin, Message);
        memcpy(Buffer, Message.c_str(), Message.size());
        int SendBytes = send(ClientSocket, Buffer, strlen(Buffer), 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]Server Send Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            cout << "[SYS]Server Send Message : " << Buffer << endl;
        }
        */
#pragma  endregion
#pragma  region --EXAM_03-------------------------------------------------------------------------
        /*
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]Server Recv Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        cout << "Received!" << endl;
        MessagePack RcvMsgPack = { 0, };
        memcpy(&RcvMsgPack, Buffer, RecvBytes);

        cout << "RcvMsgPack NumA :" << RcvMsgPack.NumA << ", NumB : " << RcvMsgPack.NumB << endl;
        */

#pragma  endregion
        //int sendbytes = 0;
        //int recvbytes = 0;
        //int number1 = 0;
        //int number2 = 0;
        //
        //memset(Buffer, 0, PACKET_SIZE);
        //recvbytes = recv(ClientSocket, Buffer, int(sizeof(Buffer) - 1), 0);
        //cout << "Recv 1 Bytes : " << recvbytes << endl;
        //number1 = atoi(Buffer);
        //
        //recvbytes = recv(ClientSocket, Buffer, int(sizeof(Buffer) - 1), 0);
        //cout << "Recv 2 Bytes : " << recvbytes << endl;
        //number2 = atoi(Buffer);
        //
        //int number3 = number1 + number2;
        //
        //memset(Buffer, 0, PACKET_SIZE);
        //_itoa(number3, Buffer, 10);
        //sendbytes = send(ClientSocket, Buffer,(int)(strlen(Buffer)+1), 0);
        //cout << "Send bytes : " << sendbytes << endl;
        //cout << "answer : " << Buffer << endl;
        //MessagePack recvdata;
        //MessagePack senddata;
        //
        //int recvbytes = 0;
        //int sendbytes = 0;
        //
        //recvbytes = recv(ClientSocket, (char*)&recvdata, sizeof(recvdata),0);
        //recvdata.NumA = ntohl(recvdata.NumA); //Network to host
        //recvdata.NumB = ntohl(recvdata.NumB); //Network to host
        //senddata.NumA = htonl(recvdata.NumA + recvdata.NumB);
        //sendbytes = send(ClientSocket, (char*)&senddata, sizeof(senddata), 0);
#pragma region --EXAM_04-----------------------------------------------------------------
        FILE * fp = fopen("background.jpg", "rb");
        if (fp)
        {
            int fileSizeBytes = GetFileSizeBytes("background.png");
            int fileReadBytes = 0;
            int totalFileReadBytes = 0;
            //Send Message Header : FileSizeBytes
            send(ClientSocket, (char*)&fileSizeBytes, sizeof(fileSizeBytes), 0);
            while (!feof(fp))
            {
                //Send Message Body : File
                fileReadBytes = fread(Buffer, sizeof(char), sizeof(Buffer), fp);
                send(ClientSocket, Buffer, fileReadBytes, 0);
                totalFileReadBytes += fileReadBytes;
            }
            fclose(fp);
        }
        bExitCalled = true;
#pragma endregion
    } while (!bExitCalled);

    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    if (ServerSocket) { closesocket(ServerSocket); ServerSocket = NULL; }
    WSACleanup();
    return 0;
}
