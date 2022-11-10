//���� ������ �Ҿ����� ���ȿ� ������ �ִ� �Լ��� �����ϰ� ���ڴ�.
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>
//��ǻ�Ͱ� ����� �ϱ� ���� ����� ���ǵǾ� �ִ� ��������� �ҷ��´�.
#include <winsock2.h>

//��ǻ�Ͱ� ����� �ϱ� ���� ����� ������ ���ǵǾ� �ִ� ���̺귯���� �ҷ��´�.
#pragma comment(lib, "WS2_32.lib")

using namespace std;

void main()
{
    //��ǻ�Ͱ� ����� �ϱ� ���� ��� ����(����ü)�� �غ��Ѵ�.
    //��ǻ�Ͱ� ����� �ϱ� ���� ����� �ü������ �����Ѵ�.
    WSAData wsadata;

    //��ǻ�Ͱ� ����� �ϱ� ���� ����� �ʱ�ȭ�Ѵ�.
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //IP�ּҸ� �θ��� ��Ģ 2���� [AF_INET = IPV4 (192.168.1.1) : ���־���], [AF_INET6 = IPV6 (fe80::a972:ab9b:1486:901b%10)]
    //SOCK_STREAM : TCP�� ���Ŵ�, SOCK_DGRAM : UDP�� ���Ŵ�.
    //IPPROTO_TCP : TCP�� ���Ŵ�, IPPROTO_UDP : UDP�� ���Ŵ�, 0 : AUTO����
    SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    ServerAddress.sin_port = htons(5001); 
    /*----------------------------------------------------------------------
        ������ �ü���� Little Endian�̶�� ����� ����.
        ������ �ü���� Big Endian�̶�� ����� ����.
        ��Ʈ��ũ ����� Big Endian�̶�� ����� ����.
        ������ �ü���� ��Ʈ��ũ ����� ����� �ٸ��� ������, ���ߴ� �۾��� �ϱ� ���ؼ�
        Host to Network ���� �Լ��� ����.
        htons(short) : Little Endian -> Big Endian���� �ٲ۴�. (2����Ʈ)
        htonl(int) : Little Endian -> Big Endian���� �ٲ۴�.  (4����Ʈ)

        ntohs(short) : Big Endian -> Little Endian���� �ٲ۴�. (2����Ʈ)
        ntohl(int) : Big Endian -> Little Endian���� �ٲ۴�.  (4����Ʈ)


        ��Ʈ �����Ҷ� ������ 0000 0000 (0) ~ 1111 1111 (255)
                     16���� 0~F A=10, B=11, C=12, D=13, E=14, F=15
                     16���� 00 ~ FF
                     16���� 1 = 10���� : 01
                     16���� 2 = 10���� : 02
                     16���� 3 = 10���� : 03
                     16���� 4 = 10���� : 04
                     16���� 5 = 10���� : 05
                     16���� 6 = 10���� : 06
                     16���� 7 = 10���� : 07
                     16���� 8 = 10���� : 08
                     16���� 9 = 10���� : 09
                     16���� A = 10���� : 10
                     16���� B = 10���� : 11
                     16���� C = 10���� : 12
                     16���� D = 10���� : 13
                     16���� E = 10���� : 14
                     16���� F = 10���� : 15

                     1F = 1 * 16^1 + F(15) * 16^0 = 31
                     2F = 32 + 15 = 
                     3D = 48 + 13 = 61
                     FF = 16*15 + 15 = 255

                     FFFF = �����Ʈ : 2����Ʈ 
                     SHORT 2����Ʈ

                     0000 ~ FFFF = 65536  0 ~ 65535
                     
                     00 01(BE) = 1
                     01 00(LE) = ?

                     00 00 00 01(BE) = 1
                     01 00 00 00(LE) = ???


    ----------------------------------------------------------------------*/
    //0001~1024 : �� �˷��� ��Ʈ(Well Known Port)
    //https://ko.wikipedia.org/wiki/TCP/UDP%EC%9D%98_%ED%8F%AC%ED%8A%B8_%EB%AA%A9%EB%A1%9D
    
    connect(ClientSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
    //send(); //TCP ���� �Լ� (������)
    //recv(); //TCP ���� �Լ� (�ޱ�)
    //sendto(); //UDP ���� �Լ� (������)
    //recvfrom(); //UDP ���� �Լ� (�ޱ�)
    //---------------------------------------------------------------------------
    //'h','e','l','l','o','\0'
    char message[6] = { 'h','e','l','l','o','\0' };
    send(ClientSocket, message, 6, 0);
    //---------------------------------------------------------------------------
    //�������� �ȳ����輼��.....
    closesocket(ClientSocket);
    //��ǻ�Ͱ� ����� �ϱ� ���� ����� �ٽ�ٰ� �ü������ �˷��ش�.
    WSACleanup();
}