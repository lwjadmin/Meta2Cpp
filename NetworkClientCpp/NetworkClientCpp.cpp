#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 5001
#define PACKET_SIZE 1024

struct MessagePack
{
    int NumA;
    int NumB;
};

int main(int argc, char* argv[])
//int NetworkClientCpp_main(int argc, char* argv[])
{
    bool bExitCalled = false;
    bool bConnectionSuccess = false;
    WSADATA WSAData = { 0, };
    SOCKET ServerSocket = NULL;
    SOCKET ClientSocket = NULL;
    SOCKADDR_IN ServerAddress = { 0, };
    SOCKADDR_IN ClientAddress = { 0, };
    char Buffer[PACKET_SIZE];
    string Message = "";
    int Result = 0;


    //--Init WinSock 2.2------------------------------------------------------------
    //윈소켓2.2를 쓸 준비를 한다.
    Result = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (Result != 0)
    {
        cout << "[ERR]WinSock2.2 Init Error! ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    //--Set ServerAddress-----------------------------------------------------------
    //연결할 TCP서버의 주소와 포트를 지정한다. 
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerAddress.sin_port = htons(SERVER_PORT);
    do
    {
        //--Wait for Server Connection-----------------------------------------------
        if (!bConnectionSuccess)
        {
            cout << "[SYS]TCPClient Try to Connect TCPServer...";
            //연결이 실패할 경우, 소켓을 닫고 다시 만들기 위해서 해당 구문 추가
            if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
            //TCP소켓을 만든다. 
            ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if (ClientSocket == INVALID_SOCKET)
            {
                cout << "\n[ERR]ClientSocket Creation Error! ErrorCode : " << GetLastError() << endl;
                continue;
            }
            //TCP서버와의 연결을 시도한다. 
            Result = connect(ClientSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
            if (Result == SOCKET_ERROR)
            {
                cout << "\n[ERR]ClientSocket Connection Failed! ErrorCode : " << GetLastError() << endl;
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
        //--SEND---------------------------------------------------------------------
        memset(Buffer, 0, PACKET_SIZE);
        cout << "[SYS]Input Send Message : ";
        getline(cin, Message);
        memcpy(Buffer, Message.c_str(), Message.size());
        int SendBytes = send(ClientSocket, Buffer, (size_t)strlen(Buffer), 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]Client Send Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            cout << "[SYS]Client Send Message : " << Message << endl;
        }
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]Client Recv Error : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        if (Buffer[0] == 'K' && Buffer[1] == 'I' && Buffer[2] == 'L' && Buffer[3] == 'L')
        {
            bExitCalled = true;
            break;
        }
        cout << "OK!\n[SYS]Client Received Message : " << Buffer << endl;
        */
#pragma  endregion
#pragma  region --EXAM_02-------------------------------------------------------------------------
        /*
        //--RECV---------------------------------------------------------------------
        cout << "[SYS]Waiting For Message...";
        memset(Buffer, 0, PACKET_SIZE);
        int RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes <= 0)
        {
            cout << "\n[ERR]Client Recv Error : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        if (Buffer[0] == 'K' && Buffer[1] == 'I' && Buffer[2] == 'L' && Buffer[3] == 'L')
        {
            bExitCalled = true;
            break;
        }
        cout << "OK!\n[SYS]Client Received Message : " << Buffer << endl;
        */
#pragma  endregion
#pragma  region --EXAM_03-------------------------------------------------------------------------
        /*
        //--SEND---------------------------------------------------------------------
        //보낼 버퍼를 초기화한다.
        memset(Buffer, 0, PACKET_SIZE);
        cout << "[SYS]Input Send Two Integers [EX)1 2] : ";
        //구조체를 할당한다음, 구조체 메모리 영역을 보낼 버퍼에 쓴다.
        MessagePack SendMsgPack = { 0, };
        cin >> SendMsgPack.NumA >> SendMsgPack.NumB;
        memcpy(Buffer, &SendMsgPack, sizeof(MessagePack));
        //send Flags : TCP/UDP가 아닌 다른 프로토콜을 사용할 때 사용한다.
        //             TCP/UDP에서는 0(사용하지 않음)
        //구조체 크기만큼 TCP서버로 쏜다.
        int SendBytes = send(ClientSocket, Buffer, sizeof(MessagePack), 0);
        if (SendBytes <= 0)
        {
            cout << "[ERR]Client Send Error! ErrorCode : " << GetLastError() << endl;
            bConnectionSuccess = false;
            continue;
        }
        else
        {
            cout << "[SYS]Client Send Message Bytes : " << SendBytes << endl;
        }
        */
        /*
        //int sendbytes = 0;
        //int recvbytes = 0;
        //MessagePack recvdata;
        //MessagePack senddata;
        //int number1 = 0;
        //int number2 = 0;
        //cin >> number1;
        //cin >> number2;
        //memset(Buffer, 0, PACKET_SIZE);
        //_itoa(number1, Buffer, 10);
        ////--------------------------------------------------------------------------
        //// Send : 한번에 보낼수도, 쪼개서 보낼수도 있다.
        //// Send 호출시, OS의 TCPBuffer에 보내준다.
        ////--------------------------------------------------------------------------
        //sendbytes = send(ClientSocket, Buffer, strlen(Buffer) + 1, 0); //'1','0','\n'
        //cout << "Send 1 Bytes : " << sendbytes << endl;
        //_itoa(number2, Buffer, 10);
        //sendbytes = send(ClientSocket, Buffer, strlen(Buffer) + 1, 0); //'2','0','\n'
        //cout << "Send 2 Bytes : " << sendbytes << endl;
        //memset(Buffer, 0, PACKET_SIZE);
        //recvbytes = recv(ClientSocket, Buffer, sizeof(Buffer) - 1, 0); //'3','0','\n'
        //cout << "Recv Bytes : " << recvbytes << endl;
        //cout << "Result : " << Buffer << endl;

        //senddata.NumA = htonl(10); //Host to Network
        //senddata.NumB = htonl(20); //Host to Network
        //sendbytes = send(ClientSocket, (char*)&senddata, sizeof(senddata), 0);
        //recvbytes = recv(ClientSocket, (char*)&recvdata, sizeof(recvdata), 0);
        //
        //recvdata.NumA = ntohl(recvdata.NumA);
        //cout << "RecvData.NumA : " << recvdata.NumA << endl;
        */
#pragma  endregion
#pragma region --EXAM_04-----------------------------------------------------------------
        FILE * fp = fopen("downloaded.png", "wb");
        int fileSizeBytes = 0;
        int RecvBytes = 0;
        int totalRecvBytes = 0;
        //--CASE 1 : 파일 크기를 메시지 헤더로 받았을 경우 -----------------------------------------
        recv(ClientSocket, (char*)&fileSizeBytes, sizeof(fileSizeBytes), 0);
        while (!(totalRecvBytes >= fileSizeBytes))
        {
            RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
            totalRecvBytes += RecvBytes;
            fwrite(Buffer, 1, RecvBytes, fp);
            float DownloadedPercent = (int)((float)totalRecvBytes / (float)fileSizeBytes * 100.0f);
            cout << "Download Bytes : " << totalRecvBytes << " / " << fileSizeBytes << "(" << DownloadedPercent << "%)" << endl;
        }
        //--CASE 2 : 파일 크기를 메시지 헤더로 못받을 경우 ------------------------------------------
        //while (RecvBytes != 0)
        //{
        //    RecvBytes = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
        //    fwrite(Buffer, sizeof(char), RecvBytes, fp);
        //    totalRecvBytes += RecvBytes;
        //}
        cout << "Download Completed!" << endl;
        if (fp != NULL) { fclose(fp); fp = NULL; }
        bExitCalled = true;
#pragma endregion
    } while (!bExitCalled);

    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    if (ServerSocket) { closesocket(ServerSocket); ServerSocket = NULL; }
    WSACleanup();
    return 0;
}
