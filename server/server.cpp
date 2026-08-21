    #include <iostream>
    #include <thread>
    #include <winsock2.h>

    using namespace std;

    void send_to_client2(SOCKET clientsocket1, SOCKET clientsocket2){//클라1 스레드
        while(1){
            char buffer[2025];
            int received=recv(clientsocket1, buffer, sizeof(buffer)-1, 0);

            if(received>0){
                buffer[received]='\0';
                cout<<"client 1 : "<<buffer<<'\n';
                send(clientsocket2,buffer,received,0);
            }
            else if(received==0){
                cout<<"cilent 1 disconnected\n";
                break;
            }
            else{
                cout<<"client 1 recv failed : "<<WSAGetLastError()<<'\n';
                break;
            }
        }
    }
    void send_to_client1(SOCKET clientsocket2, SOCKET clientsocket1){//클라2 스레드
        while(1){
            char buffer[2025];
            int received=recv(clientsocket2, buffer, sizeof(buffer)-1, 0);

            if(received>0){
                buffer[received]='\0';
                cout<<"client 2 : "<<buffer<<'\n';
                send(clientsocket1,buffer,received,0);
            }
            else if(received==0){
                cout<<"cilent 2 disconnected\n";
                break;
            }
            else{
                cout<<"client 2 recv failed : "<<WSAGetLastError()<<'\n';
                break;
            }
        }
    }
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

        if(listen(serverSocket,SOMAXCONN)==SOCKET_ERROR){//클라이언트 연결대기
            cout<<"listen failed\n";
            return 1;
        }
        else{
            cout<<"listen success\n";
        }

        sockaddr_in clientadd1{};//클라이언트 연결을 위한 클라이언트소켓구조체1 생성
        int clientsize1=sizeof(clientadd1);

        SOCKET clientsocket1=accept(serverSocket,(sockaddr*)&clientadd1,&clientsize1);

        if(clientsocket1==INVALID_SOCKET){
            cout<<"client1 accept failed\n";
            return 1;
        }
        else{
            cout<<"client1 accept connected\n";
        }

        sockaddr_in clientadd2{};//클라이언트 연결을 위한 클라이언트소켓구조체2 생성
        int clientsize2=sizeof(clientadd2);

        SOCKET clientsocket2=accept(serverSocket,(sockaddr*)&clientadd2,&clientsize2);

        if(clientsocket2==INVALID_SOCKET){
            cout<<"client2 accept failed\n";
            closesocket(clientsocket1);
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
        else{
            cout<<"client2 accept connected\n";
        }

        thread client1_thread(send_to_client2,clientsocket1,clientsocket2);
        thread client2_thread(send_to_client1,clientsocket2,clientsocket1);

        client1_thread.join();
        client2_thread.join();

        return 0;
    }