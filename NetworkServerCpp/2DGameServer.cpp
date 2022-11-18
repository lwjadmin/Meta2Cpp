#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <process.h>
#include <Windows.h>
#include <timeapi.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#pragma comment(lib,"WS2_32.lib")

using namespace std;

#define SERVER_IPV4 "0.0.0.0"
#define SERVER_PORT 4949
#define PACKET_SIZE 1024

#define GEngine MyGameEngine::getInstance()

class PlayerController
{
public:
    Vector2D PlayerPos;
    SOCKET ClientSocket;
    SOCKADDR_IN ClientAddress;
    int szClientAddress;
    CRITICAL_SECTION mCSTxSocket;
    queue<string> TxQueue;
    bool isAlive = false;

    PlayerController()
    {
        InitializeCriticalSection(&mCSTxSocket);
        PlayerPos = Vector2D(0, 0);
        ClientSocket = NULL;
        szClientAddress = sizeof(ClientAddress);
        memset(&ClientAddress, 0, szClientAddress);
        isAlive = true;
    }

    ~PlayerController()
    {
        if (ClientSocket) { closesocket(ClientSocket); }
        DeleteCriticalSection(&mCSTxSocket);
    }

    void SendMsg_PlayerCreatiton()
    {
        char buffer[1024] = { 0, };
        strcpy(buffer, "PLAYERCREATION");
        EnterCriticalSection(&mCSTxSocket);
        TxQueue.push(buffer);
        LeaveCriticalSection(&mCSTxSocket);
    }
};

struct Vector2D
{
    int X;
    int Y;

    Vector2D()
    {
        X = 0;
        Y = 0;
    }

    Vector2D(int InX, int InY)
    {
        X = InX;
        Y = InY;
    }
};

class GameThread
{
public:
    CRITICAL_SECTION mSection;
    HANDLE mHandle;
    int mID;

    GameThread()
    {
        InitializeCriticalSection(&mSection);
    }
    void Start()
    {

    }
    void Stop()
    {

    }
    ~GameThread()
    {
        DeleteCriticalSection(&mSection);
    }
};

class GameThreadPool
{
    
};

class GameEngine
{
private:
    static GameEngine instance;
public:
    static GameEngine getInstance()
    {
        return instance;
    }
private:
    GameEngine()
    {
        WSAStartup(MAKEWORD(2, 2), &mWSAData);

    }
    ~GameEngine()
    {
        WSACleanup();
    }
public:
    WSAData mWSAData;
    SOCKET mServerSocket;
    SOCKADDR_IN mServerAddr;
    vector<PlayerController*> mvPlayerController;
    CRITICAL_SECTION mvPlayerController_CS;
    vector<GameThread*> mvGameThread;
    int* Map;

    bool bIsRunning = false;

    bool Init()
    {
        bool isS = false;
        do
        {
            mServerSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (mServerSocket == INVALID_SOCKET) { break; }
            mServerAddr.sin_family = AF_INET;
            mServerAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IPV4);
            mServerAddr.sin_port = htons(SERVER_PORT);
            if (bind(mServerSocket, (sockaddr*)&mServerAddr, sizeof(mServerAddr)) != 0) { break; }
            if (listen(mServerSocket, SOMAXCONN) != 0) { break; }
            isS = true;
        } while (false);
        return isS;
    }

    bool Start()
    {
        bool InitSuccess = Init();
        if (InitSuccess)
        {
            bIsRunning = true;
            GameThread* thread = new GameThread(GameResourceMgnt, nullptr);
            thread->Start();

            while (!GetbIsRunning())
            {
                PlayerController* pc = new PlayerController();
                pc->ClientSocket = accept(mServerSocket, (sockaddr*)&pc->ClientAddress, &pc->szClientAddress);
                EnterCriticalSection(&mvPlayerController_CS);
                mvPlayerController.push_back(pc);
                LeaveCriticalSection(&mvPlayerController_CS);
                GameThread* threadTx = new GameThread(GameThread_PlayerNetworkTx, pc);
                threadTx->Start();
                mvGameThread.push_back(threadTx);
                GameThread* threadRx = new GameThread(GameThread_PlayerNetworkRx, pc);
                threadRx->Start();
                mvGameThread.push_back(threadTx);
                pc->SendMsg_PlayerCreatiton();
            }
        }
    }

    bool Stop()
    {
        bIsRunning = false;

        if (mServerSocket) { closesocket(mServerSocket); }
        WSACleanup();
    }
    

    void DoPlayerControllerManagement()
    {
        while (!GEngine.bIsRunning)
        {
            for (int i = mvPlayerController.size(); i >= 0; i--)
            {
                if (!mvPlayerController[i]->isAlive)
                {
                    mvPlayerController.erase(mvPlayerController[i]);
                }
            }
        }
        //Clear All PlayerController       
    }

    void DoGameThreadManagement()
    {
        while (!GEngine.bIsRunning)
        {
            for (auto itr = GGame->mPlayerList.rbegin(); itr != GGame->mPlayerList.rend(); itr++)
            {
                delete(itr);
                GGame->mPlayerList.erase(itr);
            }
        }
        //Clear ALL Thread
    }

    void DoRenderMap()
    {

    }

    static unsigned WINAPI GameResourceMgnt(void* args)
    {
        while (true)
        {
            Sleep(1000);
            DoPlayerControllerManagement();
            DoGameThreadManagement();
        }
        return 0;
    }

    static unsigned WINAPI GameThread_PlayerNetworkRx(void* args)
    {
        PlayerController controller = *(PlayerController*)args;
        while (true)
        {
            char buf[PACKET_SIZE] = { 0, };
            int recvBytes = recv(pInfo.ClientSocket, buf, sizeof(buf), 0);
            for (int i = 0; i < GGame->mPlayerList.size(); i++)
            {
                if (buf->msgID == UpdatePlayerPos)
                {
                    UpdatePlayerPos();
                }

                if (GGame->mPlayerList[i] != pInfo)
                {
                    int sendBytes = send(pInfo.ClientSocket, buf, sizeof(buf), 0);
                }
            }
        }
        pInfo.isAlive = false;
        return 0;
    }

    static unsigned WINAPI GameThread_PlayerNetworkTx(void* args)
    {
        PlayerController controller = *(PlayerController*)args;
        while (true)
        {
            if (!pInfo.TxQueue.empty())
            {
                string msg = pInfo.TxQueue.front();
                switch (msg.msgID)
                {
                    case 1:
                    {
                        //
                    }
                    case 2:
                    {

                    }
                }
                pInfo.TxQueue.pop();
            }
        }
        pInfo.isAlive = false;
        return 0;
    }
};



int main(int argc, char* argv[])
{
    GEngine->Start();
    while (true)
    {
        char InputKey = _getch();
        if (InputKey == 'q')
        {
            break;
        }
    }
    GEngine->Stop();
    return 0;
}