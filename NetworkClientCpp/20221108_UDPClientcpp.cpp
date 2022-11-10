#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 1234
#define PACKET_SIZE 1024

#include <string>
#include <iostream>
#include <WinSock2.h>
#include <thread>

using namespace std;

int L20221108_UDPClient_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    WSADATA WSAData;
    int retval = 0;

    retval = WSAStartup(MAKEWORD(2, 2), &WSAData);
    if (retval != 0)
    {
        cout << "Winsock 2.2 Load Fail!" << endl;
        exit(-1);
    }

    SOCKET clientsocket = { 0, };
    clientsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientsocket == INVALID_SOCKET)
    {
        cout << "[ERR]Invalid Socket!" << endl;
        exit(-2);
    }
    SOCKADDR_IN ServerSocketAddress = { 0, };
    ServerSocketAddress.sin_family = AF_INET;
    ServerSocketAddress.sin_port = htons(SERVER_PORT);
    ServerSocketAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


    while (true)
    {
        char buffer[1024] = { 0, };
        strcpy(buffer, "udpudp");
        int sendbytes = sendto(clientsocket, buffer, strlen(buffer), 0, (sockaddr*)&ServerSocketAddress, sizeof(ServerSocketAddress));

        SOCKADDR_IN RemoteSocketAddress = { 0, };
        int szRemoteSocketAddress = sizeof(RemoteSocketAddress);
        int recvbytes = recvfrom(clientsocket, buffer, sizeof(buffer), 0, (sockaddr*)&RemoteSocketAddress, &szRemoteSocketAddress);
        if (recvbytes == 0)
        {
            cout << "UDPServer Connection Closed Complete." << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else if (recvbytes == SOCKET_ERROR)
        {
            cout << "UDPClient Socket Error! ErrorCode : " << GetLastError() << endl;
            this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        else
        {
            cout << buffer << endl;
            break;
        }
    }
    closesocket(clientsocket);
    WSACleanup();
    

    

    /*
    bool bExitCalled = false;
    bool bConnectionSuccess = false;
    WSADATA WSAData = { 0, };
    SOCKET ClientSocket = NULL;
    SOCKADDR_IN ServerSocketAddress = { 0, };
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
    ServerSocketAddress.sin_family = PF_INET;
    ServerSocketAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ServerSocketAddress.sin_port = htons(SERVER_PORT); //Host to Network : short Little Endian에서 short Big Endian으로 변환
    ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (ClientSocket == INVALID_SOCKET)
    {
        std::cout << "\n[ERR]ServerSocket Creation Error! ErrorCode : " << GetLastError() << std::endl;
        exit(-2);
    }
    do
    {
        SOCKADDR_IN RemoteSocketAddress = { 0, };
        int szRemoteSocketAddress = sizeof(RemoteSocketAddress);
        int SendBytes = 0;
        int RecvBytes = 0;
        std::cout << "[SYS]Input Send Message : ";
        std::getline(std::cin, Message);

        char buffer[PACKET_SIZE] = { 0, };
        memcpy(buffer, Message.c_str(), Message.size());
        SendBytes = sendto(ClientSocket, buffer, strlen(buffer), 0, (sockaddr*)&ServerSocketAddress, sizeof(ServerSocketAddress));
        
        RecvBytes = recvfrom(ClientSocket, buffer, sizeof(buffer), 0, (sockaddr*)&RemoteSocketAddress, &szRemoteSocketAddress);
        std::cout << "[SYS]UDPClient RECV Message : " << buffer << std::endl;
#pragma endregion
    } while (!bExitCalled);
    if (ClientSocket) { closesocket(ClientSocket); ClientSocket = NULL; }
    WSACleanup();
    return 0;
    */
}
