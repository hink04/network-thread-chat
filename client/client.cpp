#include <iostream>
#include <winsock2.h>
#include <thread>
using namespace std;

void sendmsg(SOCKET clientsocket){//메세지 전송
    while(1){
        char msg[1024];
        cout<<"input : ";
        cin.getline(msg,sizeof(msg));
        int sent=send(clientsocket,msg,strlen(msg),0);
        
        if(sent==SOCKET_ERROR){
            cout<<"send failed\n";
            break;
        }

    }
}

void receivemsg(SOCKET clientsocket){//메세지 받음
    while(1){
        char buffer[2025];
        int received=recv(clientsocket,buffer,sizeof(buffer)-1,0);

        if(received>0){
            buffer[received]='\0';
            cout<<"server : "<<buffer<<'\n';
        }
        else if(received==0){
            cout<<"server disconnected\n";
            break;
        }
        else{
            cout<<"recv failed : "<<WSAGetLastError()<<'\n';
            break;
        }
    }
}
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

    thread sendthread(sendmsg,clientSocket);
    thread recvthread(receivemsg,clientSocket);

    sendthread.join();
    recvthread.join();
    
    return 0;
}