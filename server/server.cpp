#include <iostream>
#include <thread>
#include <winsock2.h>

using namespace std;

int main()
{
    WSADATA wsaData;

    int result=WSAStartup(MAKEWORD(2,2),&wsaData);

    if(result==0){//WSA생성확인
        cout<<"winsock success\n";
    }
    else{
        cout<<"winsock failed\n";
        return 1;
    }

    SOCKET serverSocket=socket(AF_INET,SOCK_STREAM,0);

    if(serverSocket==INVALID_SOCKET){//소켓생성확인
        cout<<"socket failed\n";
        return 1;
    }
    else{
        cout<<"socket created\n";
    }

    sockaddr_in serveraddr{};//소켓에 주소를 설정

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(8080);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    if(bind(serverSocket,(sockaddr*)&serveraddr,sizeof(serveraddr))==SOCKET_ERROR){//소켓에 주소 부여
        cout<<"bind failed\n";
        return 1;
    }
    else{
        cout<<"bind success\n";
    }



    return 0;
}