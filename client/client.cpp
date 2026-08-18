#include <iostream>
#include <winsock2.h>

using namespace std;

int main()
{
    WSADATA wsaData;

    int result = WSAStartup(
        MAKEWORD(2, 2),
        &wsaData
    );

    if (result == 0)
    {
        cout << "Winsock success!\n";
    }
    else
    {
        cout << "Winsock failed!\n";
        return 1;
    }

    SOCKET clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "Socket failed!\n";
        return 1;
    }

    cout << "Socket created!\n";

    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(
        clientSocket,
        (sockaddr*)&serverAddr,
        sizeof(serverAddr)
    ) == SOCKET_ERROR)
    {
        cout << "Connect failed!\n";
        return 1;
    }

    cout << "Connected to server!\n";

    return 0;
}