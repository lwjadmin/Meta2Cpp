#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <timeapi.h>

#include <iostream>
#include <vector>

#pragma comment(lib,"WS2_32.lib")

#define SERVER_IPV4 "127.0.0.1"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

using namespace std;

vector<SOCKET> vSocketList;
vector<HANDLE> vHandleList;

CRITICAL_SECTION CSThread;

unsigned WINAPI WorkThread(void* args)
{
    SOCKET TCPClientSocket = *(SOCKET*)args;

    while (true)
    {
        char Buffer[PACKET_SIZE] = { 0, };
        int RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
        if (RecvBytes < 0)
        {
            break;
        }
        cout << "[Server] RECV Message : " << Buffer << endl;

        for (int i = 0; i < vSocketList.size(); i++)
        {
            if (vSocketList[i] == TCPClientSocket) { continue; }
            int SendBytes = send(vSocketList[i], Buffer, strlen(Buffer), 0);
            if (SendBytes < 0)
            {
                break;
            }
        }
    }
    if (TCPClientSocket) { closesocket(TCPClientSocket); }
    cout << "[SYS]TCPClient Disconnected." << endl;
    /*-------------------------------------------------------------------------
    MultiThread 환경에서 WorkThread 함수 동작시 Heap에 저장되는 vSocketList는 
    Thread-safe하지 않기 때문에 충돌시 프로그램이 죽을수도 있다. 
    따라서, vSocketList 접근하여 1Element 삭제하는 로직에 Critical Section으로 감싼다.
    -------------------------------------------------------------------------*/
    EnterCriticalSection(&CSThread);
    for (int i = 0; i < vSocketList.size(); i++)
    {
        if (vSocketList[i] == TCPClientSocket)
        {
            vSocketList.erase(vSocketList.begin() + i);
            break;
        }
    }
    LeaveCriticalSection(&CSThread);
    return 0;
}

int L20221118_TCPMultiplexingServer_main2(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    InitializeCriticalSection(&CSThread);
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;
    //1.Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS]Winsock 2.2 Load Complete!" << endl;
    TCPServerAddress.sin_family = AF_INET;
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    TCPServerAddress.sin_port = htons(SERVER_PORT);
    //2.Create TCPServerSocket
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS]TCPSocket Creation Complete!" << endl;
    //3.Bind TCPServerSocket to Address 
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS]TCPSocket Address Bind Complete!" << endl;
    //4.Set TCPServerSocket Listening...
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS]TCPSocket Listening..." << endl;

    /*------------------------------------------------------------------
    이 로직은 접속자가 증가할수록 무한히 스레드가 증가하기 때문에 위험하다. 
    접속자가 로그아웃할 때 노는 스레드를 죽이는 로직을 추가해야 하고, 
    스레드가 제한되어 사용될수 있도록 제한된 스레드 갯수를 만들고, 각 스레드에서
    Socket Select를 할수 있도록 구현하는 것이 좀더 안정적이다!

    데이터가 들어오면 큐에 넣는 스레드를 하나 만들고,
    큐를 하나 빼서 데이터를 처리하는 스레드를 하나 만드는 것이 좋다. 
    ------------------------------------------------------------------*/
    while (true)
    {
        SOCKADDR_IN TCPClientAddress = { 0, };
        int szTCPClientAddress = sizeof(TCPClientAddress);
        SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
        vSocketList.push_back(TCPClientSocket);
        HANDLE WorkHandle = (HANDLE)_beginthreadex(nullptr, 0, WorkThread, (void*)&TCPClientSocket, 0, nullptr);
        EnterCriticalSection(&CSThread);
        vHandleList.push_back(WorkHandle);
        LeaveCriticalSection(&CSThread);
        cout << "[SYS]New TCPClient Connected." << endl;
    }//eowhile

    for (int i = 0; i < vHandleList.size(); i++)
    {
        TerminateThread(vHandleList[i], -1);
        CloseHandle(vHandleList[i]);
    }
    vHandleList.clear();
    DeleteCriticalSection(&CSThread);

    if (TCPServerSocket) { closesocket(TCPServerSocket); }
    WSACleanup();
    return 0;
}

int L20221118_TCPMultiplexingServer_main1(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    WSAData wsadata = { 0, };
    SOCKET TCPServerSocket = NULL;
    SOCKADDR_IN TCPServerAddress = { 0, };
    int Retval = 0;
    //1.Load Winsock2.2
    Retval = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (Retval != 0)
    {
        cout << "[ERR]Winsock 2.2 Load Failed. ErrorCode : " << GetLastError() << endl;
        exit(-1);
    }
    cout << "[SYS]Winsock 2.2 Load Complete!" << endl;
    TCPServerAddress.sin_family = AF_INET;
    TCPServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
    TCPServerAddress.sin_port = htons(SERVER_PORT);
    //2.Create TCPServerSocket
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
    if (TCPServerSocket == INVALID_SOCKET)
    {
        cout << "[ERR]TCPSocket Creation Failed! ErrorCode : " << GetLastError() << endl;
        exit(-2);
    }
    cout << "[SYS]TCPSocket Creation Complete!" << endl;
    //3.Bind TCPServerSocket to Address 
    Retval = bind(TCPServerSocket, (sockaddr*)&TCPServerAddress, sizeof(TCPServerAddress));
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Address Bind Failed! ErrorCode : " << GetLastError() << endl;
        exit(-3);
    }
    cout << "[SYS]TCPSocket Address Bind Complete!" << endl;
    //4.Set TCPServerSocket Listening...
    Retval = listen(TCPServerSocket, SOMAXCONN);
    if (Retval != 0)
    {
        cout << "[ERR]TCPSocket Listen Failed! ErrorCode : " << GetLastError() << endl;
        exit(-4);
    }
    cout << "[SYS]TCPSocket Listening..." << endl;
    //--------------------------------------------------------------------------------------------
    //Socket 구조체 배열(원본) 할당 
    fd_set reads; FD_ZERO(&reads);
    //Socket 구조체 배열(복사본) 할당
    fd_set copys; FD_ZERO(&copys);
    //TCPServerSocket의 상태를 감시하여 OS에 전달할 수 있는 구조체를 할당한다.
    FD_SET(TCPServerSocket, &reads);
    //1초마다 한번씩 감시
    TIMEVAL Timeout;
    Timeout.tv_sec = 1;
    Timeout.tv_usec = 0;
    
    while (true)
    {
        copys = reads;
        //Timeout마다 소켓상태가 바뀐 것이 있는지 확인하기!
        int fd_num = select(0, &copys, 0, 0, &Timeout);
        if (fd_num == SOCKET_ERROR)
        {
            cout << "[ERR]Select Error Occured! ErrorCode : " << GetLastError() << endl;
            exit(-5);
        }
        else if (fd_num == 0)
        {
            //바뀐 것이 없다면, Continue;
            continue;
        }
        int SendBytes = 0;
        int RecvBytes = 0;
        char Buffer[PACKET_SIZE] = { 0, };
        

        for (int i = 0; i < (int)reads.fd_count; i++)
        {
            //해당 소켓이 바뀐게 있는가?
            if (FD_ISSET(reads.fd_array[i], &copys)) //바뀐게 있느냐?
            {
                //바뀐게 있으면, 자신(리슨소켓)도 바뀌었다고 알림이 들어온다!
                //리슨소켓에서 클라 소켓 Connect를 Accpet하고 reads에 추가
                if (reads.fd_array[i] == TCPServerSocket)
                {
                    sockaddr_in TCPClientAddress = { 0, };
                    int szTCPClientAddress = sizeof(TCPClientAddress);
                    SOCKET TCPClientSocket = accept(TCPServerSocket, (sockaddr*)&TCPClientAddress, &szTCPClientAddress);
                    FD_SET(TCPClientSocket, &reads);
                    cout << "[SYS]New TCPClient Connected." << endl;
                }
                else
                {
                    memset(Buffer, 0, sizeof(Buffer));

                    SOCKET TCPClientSocket = reads.fd_array[i];
                    RecvBytes = recv(TCPClientSocket, Buffer, sizeof(Buffer), 0);
                    //버퍼를 반드시 NTS(Null Terminated String)로 만들려고 마지막 문자열을 '\0'으로 셋팅한다.
                    Buffer[sizeof(Buffer) - 1] = '\0';
                    if (RecvBytes <= 0)
                    {
                        //TCPClientSocket이 정상종료되었거나(0) 에러났을경우(SOCKET_ERROR(-1))
                        //fd_set 구조체 원본(reads)에서 빼고 소켓 닫는다.
                        FD_CLR(TCPClientSocket, &reads);
                        closesocket(TCPClientSocket);
                        cout << "[SYS]TCPClient Disconnected." << endl;
                    }
                    else
                    {
                        cout << "[SYS]TCPClient Recv Message : " << Buffer << endl;
                        for (int j = 0; j < (int)reads.fd_count; j++)
                        {
                            if (reads.fd_array[j] != TCPServerSocket && reads.fd_array[j] != TCPClientSocket)
                            {
                                //만약, reads.fd_array[j]가 TCPClientSocket일 경우, 받은 메시지를 Send한다!
                                SendBytes = send(reads.fd_array[j], Buffer, sizeof(Buffer), 0);
                                if (SendBytes <= 0)
                                {
                                    //TCPClientSocket이 정상종료되었거나(0) 에러났을경우(SOCKET_ERROR(-1))
                                    //fd_set 구조체 원본(reads)에서 빼고 소켓 닫는다.
                                    SOCKET TCPClientSocket = reads.fd_array[j];
                                    FD_CLR(TCPClientSocket, &reads);
                                    closesocket(TCPClientSocket);
                                    continue;
                                }
                                cout << "[SYS]TCPClient Send Message : " << Buffer << endl;
                            }
                        }
                    }
                }
            }//eoif_FD_ISSET
        }//eofor
    }//eowhile
    if (TCPServerSocket) { closesocket(TCPServerSocket); }
    WSACleanup();
    return 0;
}