//내가 오래된 불안정한 보안에 위험이 있는 함수를 감수하고 쓰겠다.
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <iostream>
//컴퓨터간 통신을 하기 위한 모듈이 정의되어 있는 헤더파일을 불러온다.
#include <winsock2.h>

//컴퓨터간 통신을 하기 위한 모듈이 실제로 정의되어 있는 라이브러리를 불러온다.
#pragma comment(lib, "WS2_32.lib")

using namespace std;

void main()
{
    //컴퓨터간 통신을 하기 위한 모듈 깡통(구조체)을 준비한다.
    //컴퓨터간 통신을 하기 위한 모듈은 운영체제에서 관리한다.
    WSAData wsadata;

    //컴퓨터간 통신을 하기 위한 모듈을 초기화한다.
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //IP주소를 부르는 규칙 2가지 [AF_INET = IPV4 (192.168.1.1) : 자주쓴다], [AF_INET6 = IPV6 (fe80::a972:ab9b:1486:901b%10)]
    //SOCK_STREAM : TCP를 쓸거다, SOCK_DGRAM : UDP를 쓸거다.
    //IPPROTO_TCP : TCP를 쓸거다, IPPROTO_UDP : UDP를 쓸거다, 0 : AUTO선택
    SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in ServerAddress;
    memset(&ServerAddress, 0, sizeof(ServerAddress));
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    ServerAddress.sin_port = htons(5001); 
    /*----------------------------------------------------------------------
        윈도우 운영체제는 Little Endian이라는 방식을 쓴다.
        리눅스 운영체제는 Big Endian이라는 방식을 쓴다.
        네트워크 통신은 Big Endian이라는 방식을 쓴다.
        윈도우 운영체제와 네트워크 통신의 방식이 다르기 때문에, 맞추는 작업을 하기 위해서
        Host to Network 관련 함수를 쓴다.
        htons(short) : Little Endian -> Big Endian으로 바꾼다. (2바이트)
        htonl(int) : Little Endian -> Big Endian으로 바꾼다.  (4바이트)

        ntohs(short) : Big Endian -> Little Endian으로 바꾼다. (2바이트)
        ntohl(int) : Big Endian -> Little Endian으로 바꾼다.  (4바이트)


        비트 공부할때 이진수 0000 0000 (0) ~ 1111 1111 (255)
                     16진수 0~F A=10, B=11, C=12, D=13, E=14, F=15
                     16진수 00 ~ FF
                     16진수 1 = 10진수 : 01
                     16진수 2 = 10진수 : 02
                     16진수 3 = 10진수 : 03
                     16진수 4 = 10진수 : 04
                     16진수 5 = 10진수 : 05
                     16진수 6 = 10진수 : 06
                     16진수 7 = 10진수 : 07
                     16진수 8 = 10진수 : 08
                     16진수 9 = 10진수 : 09
                     16진수 A = 10진수 : 10
                     16진수 B = 10진수 : 11
                     16진수 C = 10진수 : 12
                     16진수 D = 10진수 : 13
                     16진수 E = 10진수 : 14
                     16진수 F = 10진수 : 15

                     1F = 1 * 16^1 + F(15) * 16^0 = 31
                     2F = 32 + 15 = 
                     3D = 48 + 13 = 61
                     FF = 16*15 + 15 = 255

                     FFFF = 몇바이트 : 2바이트 
                     SHORT 2바이트

                     0000 ~ FFFF = 65536  0 ~ 65535
                     
                     00 01(BE) = 1
                     01 00(LE) = ?

                     00 00 00 01(BE) = 1
                     01 00 00 00(LE) = ???


    ----------------------------------------------------------------------*/
    //0001~1024 : 잘 알려진 포트(Well Known Port)
    //https://ko.wikipedia.org/wiki/TCP/UDP%EC%9D%98_%ED%8F%AC%ED%8A%B8_%EB%AA%A9%EB%A1%9D
    
    connect(ClientSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress));
    //send(); //TCP 전용 함수 (보내기)
    //recv(); //TCP 전용 함수 (받기)
    //sendto(); //UDP 전용 함수 (보내기)
    //recvfrom(); //UDP 전용 함수 (받기)
    //---------------------------------------------------------------------------
    //'h','e','l','l','o','\0'
    char message[6] = { 'h','e','l','l','o','\0' };
    send(ClientSocket, message, 6, 0);
    //---------------------------------------------------------------------------
    //서버에게 안녕히계세요.....
    closesocket(ClientSocket);
    //컴퓨터간 통신을 하기 위한 모듈을 다썼다고 운영체제한테 알려준다.
    WSACleanup();
}