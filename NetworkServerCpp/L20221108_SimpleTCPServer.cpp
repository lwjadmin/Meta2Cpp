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
    //��ǻ�Ͱ� ����� �ϱ� ���� ����� �����ߴ�.
    SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //�� ��ǻ�Ͱ� ������ �����ϱ� ���� IP/��Ʈ�� �����ߴ�.
    sockaddr_in ServerAddress;
    ServerAddress.sin_family = PF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    ServerAddress.sin_port = htons(5001);
    //IP/��Ʈ ���������� ��⿡ �Ҵ��ߴ�.
    bind(ServerSocket, (SOCKADDR*)&ServerAddress, sizeof(ServerAddress));
    //TCPClient�� Connect�� ������ ���Ѻ���. (���� �ȶ��ϴ��� �ʹ�� ���Ѻ���..)
    listen(ServerSocket, 0);

    //���� Connect�� ���� �ε��ٸ�, ���� �����ش�. 
    //Accept ���� send/recv�� ������ �� �ִ�.
    //�ε��� ���� ����ϱ� ���ؼ� ClientSocket�̶�� ������ �ε��� ���� ������ �����Ѵ�.
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
    //��ǻ�Ͱ� ����� �ϱ� ���� ����� �ٽ�ٰ� �ü������ �˷��ش�.
    WSACleanup();
}
