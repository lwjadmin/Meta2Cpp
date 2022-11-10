#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <vector>

#pragma comment(lib,"WS2_32.lib")

#define SERVER_PORT 4949
#define SERVER_IPV4 "127.0.0.1"

using namespace std;

/*---------------------------------------------------------
    �� TCP ��Ƽ�÷��� ����(TCP Multiplexing Server)
---------------------------------------------------------*/
int L20221108_SelectServer_main(int argc, char* argv)
//int main(int argc, char* argv)
{
    WSAData wsadata;
    //������ 2.2 ���
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    //TCP������ ���� ����
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);//IPPROTO_TCP
    sockaddr_in ListenSocketAddress = { 0, };
    ListenSocketAddress.sin_family = AF_INET;
    ListenSocketAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    ListenSocketAddress.sin_port = htons(SERVER_PORT);
    //TCP������ ���Ͽ� IP/��Ʈ �Ҵ�
    bind(listenSocket, (sockaddr*)&ListenSocketAddress, sizeof(ListenSocketAddress));
    //�ٸ� TCPŬ���̾�Ʈ�� Connect�� TCP������ ������ ��û�ϴ��� ���� 
    listen(listenSocket, SOMAXCONN);  //10k Problem

    //FD_ZERO, FD_SET, FD_ISSET, FD_CLR, select Ȯ���غ���!!
    /*------------------------------------------------------------------------
    select �Լ� : ���� ���� ������ �׷����� ���¸� üũ�Ѵ�.
    FD_ZERO : FD_SET�� ��� ����ü�� 0���� �ʱ�ȭ!
    fd_set : ������ �迭
    FD_SET :
    ------------------------------------------------------------------------*/
    //Socket ����ü �迭(����) �Ҵ� 
    fd_set reads;
    //Socket ����ü �迭(���纻)
    fd_set copys;
    //����ü�� �ʱ�ȭ�Ѵ�.
    FD_ZERO(&reads);
    //listen������ �����ϴ� OS�� ������ �� �ִ� ����ü�� �Ҵ��Ѵ�.
    FD_SET(listenSocket, &reads);
    //1010ms ���� �ѹ��� �����Ұž�!
    TIMEVAL Timeout;
    Timeout.tv_sec = 0;
    Timeout.tv_usec = 5000;

    while (true)
    {
        //���� ����!
        copys = reads;
        //1. Ÿ�Ӿƿ�(N��)���� �ٸ� ������ �����ߴ��� Ȯ���ϱ�!
        //select ���ϰ� : �ٲ�� �ִ���(���� connect ���ȴ���) Ȯ���ϱ�!!
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

        //Select�� ���� : �ٲ� ��� �迭�� �ϳ��ϳ� üũ�ؾ߸� �Ѵ�. 
        for (int i = 0; i < (int)reads.fd_count; i++)
        {
            //OS�� ���ü��� �ٲ���ٴ� �� �� �ٲ����?
            //**fd_array : 64������ ��� (SetSocketOption���� �ٲܼ� �ִ�.)
            //fd_array[FD_SETSIZE], FD_SETSIZE = 64;
            //�ش� ������ �ٲ�� �ִ°�?
            if (FD_ISSET(reads.fd_array[i], &copys)) //�ٲ�� �ִ���?
            {
                //�ٲ�� ������, �ڽ�(��������)�� �ٲ���ٰ� �˸��� ���´�!
                //�������Ͽ��� Ŭ�� ���� Connect�� Accpet�ϰ� reads�� �߰�
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
                    int recvLength = recv(reads.fd_array[i], Buffer, sizeof(Buffer) - 1, 0); //-1 : �������� �־ NTS�� �������

                    //messageList.push_back(Buffer);
                    cout << "Client Send Message : " << Buffer << endl;

                    if (recvLength <= 0) //ClientSocket�� ��������Ǿ��ų�(0) �����������(-1)
                    {
                        //���� fd_set ����ü ����(reads)���� ���� ���� �ݴ´�.
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
                                //���������� �ƴҰ�� ���ۿ� �ִ� ������ 
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