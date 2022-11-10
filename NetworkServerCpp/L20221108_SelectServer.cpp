#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <vector>

#pragma comment(lib,"WS2_32.lib")

#define SERVER_PORT 4949
#define SERVER_IPV4 "127.0.0.1"

using namespace std;

/*---------------------------------------------------------
    ※ TCP 멀티플렉싱 서버(TCP Multiplexing Server)
---------------------------------------------------------*/
int L20221108_SelectServer_main(int argc, char* argv)
//int main(int argc, char* argv)
{
    WSAData wsadata;
    //윈소켓 2.2 사용
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    //TCP서버용 소켓 생성
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);//IPPROTO_TCP
    sockaddr_in ListenSocketAddress = { 0, };
    ListenSocketAddress.sin_family = AF_INET;
    ListenSocketAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ListenSocketAddress.sin_port = htons(SERVER_PORT);
    //TCP서버용 소켓에 IP/포트 할당
    bind(listenSocket, (sockaddr*)&ListenSocketAddress, sizeof(ListenSocketAddress));
    //다른 TCP클라이언트가 Connect로 TCP서버로 접속을 요청하는지 감시 
    listen(listenSocket, SOMAXCONN);  //10k Problem

    //FD_ZERO, FD_SET, FD_ISSET, FD_CLR, select 확인해보기!!
    /*------------------------------------------------------------------------
    select 함수 : 여러 개의 소켓을 그룹지어 상태를 체크한다.
    FD_ZERO : FD_SET의 모든 구조체를 0으로 초기화!
    fd_set : 소켓의 배열
    FD_SET :
    ------------------------------------------------------------------------*/
    //Socket 구조체 배열(원본) 할당 
    fd_set reads;
    //Socket 구조체 배열(복사본)
    fd_set copys;
    //구조체를 초기화한다.
    FD_ZERO(&reads);
    //listen소켓을 감시하는 OS에 전달할 수 있는 구조체를 할당한다.
    FD_SET(listenSocket, &reads);
    //1010ms 마다 한번씩 감시할거야!
    TIMEVAL Timeout;
    Timeout.tv_sec = 0;
    Timeout.tv_usec = 5000;

    while (true)
    {
        //원본 복사!
        copys = reads;
        //1. 타임아웃(N초)마다 다른 소켓이 접속했는지 확인하기!
        //select 리턴값 : 바뀐게 있는지(누가 connect 때렸는지) 확인하기!!
        int fd_num = select(0, &copys, 0, 0, &Timeout);
        if (fd_num == SOCKET_ERROR)
        {
            cout << "[ERR]Error!" << endl;
            exit(-1);
        }
        else if (fd_num == 0) // On Timeout
        {
            continue;
        }

        //Select의 단점 : 바뀐 모든 배열을 하나하나 체크해야만 한다. 
        for (int i = 0; i < (int)reads.fd_count; i++)
        {
            //OS가 감시소켓 바뀌었다는 데 너 바뀌었냐?
            //**fd_array : 64까지만 허용 (SetSocketOption으로 바꿀수 있다.)
            //fd_array[FD_SETSIZE], FD_SETSIZE = 64;
            //해당 소켓이 바뀐게 있는가?
            if (FD_ISSET(reads.fd_array[i], &copys)) //바뀐게 있느냐?
            {
                //바뀐게 있으면, 자신(리슨소켓)도 바뀌었다고 알림이 들어온다!
                //리슨소켓에서 클라 소켓 Connect를 Accpet하고 reads에 추가
                if (reads.fd_array[i] == listenSocket)
                {
                    sockaddr_in ClientSocketAddress = { 0, };
                    int szClientSocketAddress = sizeof(ClientSocketAddress);
                    SOCKET ClientSocket = accept(listenSocket, (sockaddr*)&ClientSocketAddress, &szClientSocketAddress);
                    FD_SET(ClientSocket, &reads);
                }
                else
                {
                    char Buffer[1024] = { 0, };
                    int recvLength = recv(reads.fd_array[i], Buffer, sizeof(Buffer) - 1, 0); //-1 : 무슨일이 있어도 NTS로 만들려고

                    //messageList.push_back(Buffer);
                    cout << "Client Send Message : " << Buffer << endl;

                    if (recvLength <= 0) //ClientSocket이 정상종료되었거나(0) 에러났을경우(-1)
                    {
                        //원본 fd_set 구조체 원본(reads)에서 빼고 소켓 닫는다.
                        SOCKET disconnectSocket = reads.fd_array[i];
                        FD_CLR(disconnectSocket, &reads);
                        closesocket(disconnectSocket);
                    }
                    else
                    {
                        for (int j = 0; j < (int)reads.fd_count; j++)
                        {
                            if (reads.fd_array[j] != listenSocket)
                            {
                                //리슨소켓이 아닐경우 버퍼에 있는 내용을 
                                //for (int i = 0; i < messageList.size(); i++)
                                //{
                                //    messageList[i]
                                //}

                                int sendLength = send(reads.fd_array[i], Buffer, recvLength, 0);
                            }
                        }
                    }
                }
            }//eoif
        }//eofor
    }//eowhile
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}