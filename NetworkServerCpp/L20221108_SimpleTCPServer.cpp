#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <string>
#include <iostream>
#include <WinSock2.h>

using namespace std;

#pragma comment(lib, "WS2_32.lib") //WinSock2.DLL Load

void main()
{
    WSAData wsadata;

    WSAStartup(MAKEWORD(2, 2), &wsadata);
    //컴퓨터간 통신을 하기 위한 모듈을 정의했다.
    SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //이 컴퓨터가 서버로 동작하기 위한 IP/포트를 설정했다.
    sockaddr_in ServerAddress;
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    ServerAddress.sin_port = htons(5001);
    //IP/포트 설정정보를 모듈에 할당했다.
    bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
    //TCPClient의 Connect를 유심히 지켜본다. (누가 똑똑하는지 귀대고 지켜본다..)
    listen(ServerSocket, 0);

    //누가 Connect로 문을 두들긴다면, 문을 열어준다. 
    //Accept 이후 send/recv를 수행할 수 있다.
    //두들기는 놈을 기억하기 위해서 ClientSocket이라는 변수에 두들기는 놈의 정보를 저장한다.
    sockaddr_in ClientAddress;
    int sizeClientAddress = sizeof(ClientAddress);
    SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddress, &sizeClientAddress);
    //---------------------------------------------------------------------------
    char buffer[100];
    memset(buffer, 0, 100);
    recv(ClientSocket, buffer, 6, 0);

    cout << buffer << endl;
    //---------------------------------------------------------------------------
    closesocket(ClientSocket);
    closesocket(ServerSocket);
    //컴퓨터간 통신을 하기 위한 모듈을 다썼다고 운영체제한테 알려준다.
    WSACleanup();
}
