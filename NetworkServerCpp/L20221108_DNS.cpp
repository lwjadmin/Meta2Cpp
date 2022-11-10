#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

#include <WinSock2.h>

#pragma comment(lib, "WS2_32.lib")



using namespace std;

int L20221108_DNS_main(int argc, char* argv[])
//int main(int argc, char* argv[])
{
    WSAData wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);

    //--정방향 조회(Inverse DNS Query : 도메인을 넣으면 IP가 나옴)----------------------------------------
    hostent* host = gethostbyname("www.yahoo.com");
    cout << "** HostName : " << host->h_name << endl;
    cout << "** AliasList : " << endl;
    for (int i = 0; host->h_aliases[i]; i++)
    {
        cout << "[" << (i + 1) << "] " << host->h_aliases[i] << endl;
    }
    cout << "** host->h_addrtype : " << ((host->h_addrtype == AF_INET) ?
        "AF_INET(IPV4)" : ((host->h_addrtype == AF_INET6) ? "AF_INET6(IPV6)" : "UNKNOWN")) << endl;

    switch (host->h_length)
    {
        case 4: //IPV4
        {
            cout << "** IPList : " << endl;
            for (int i = 0; host->h_addr_list[i]; i++)
            {
                cout << "[" << (i + 1) << "] " << inet_ntoa(*(in_addr*)host->h_addr_list[i]) << endl;
            }
        }
        case 8: //IPV6
        {
            break;
        }
    }
    //--역방향 조회(Reverse DNS Query : IP를 넣으면 도메인이 나옴)----------------------------------------
    char temp[4] = { 0, };
    unsigned long IPv4 = inet_addr("202.165.107.50");
    memcpy(temp, &IPv4, sizeof(temp));


    hostent* host2 = gethostbyaddr(temp, sizeof(temp), AF_INET);
    if (!host2)
    {
        cout << "IP->Domain Not Found!" << endl;
    }
    else
    {
        cout << "** HostName : " << host2->h_name << endl;
        cout << "** AliasList : " << endl;
        for (int i = 0; host2->h_aliases[i]; i++)
        {
            cout << "[" << (i + 1) << "] " << host2->h_aliases[i] << endl;
        }
        cout << "** host->h_addrtype : " << ((host2->h_addrtype == AF_INET) ?
            "AF_INET(IPV4)" : ((host2->h_addrtype == AF_INET6) ? "AF_INET6(IPV6)" : "UNKNOWN")) << endl;

        switch (host2->h_length)
        {
            case 4: //IPV4
            {
                cout << "** IPList : " << endl;
                for (int i = 0; host2->h_addr_list[i]; i++)
                {
                    cout << "[" << (i + 1) << "] " << inet_ntoa(*(in_addr*)host2->h_addr_list[i]) << endl;
                }
            }
            case 8: //IPV6
            {
                break;
            }
        }
    }



    return 0;
}