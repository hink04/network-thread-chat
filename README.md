# Network Thread Chat

> 1:1 Chat

C++과 Winsock2, `std::thread`를 이용하여 구현한 1:1 TCP 채팅 프로그램입니다.

---

## 프로젝트 소개

이 프로젝트는 이전에 구현한 TCP Echo Server를 확장하여, 두 개의 클라이언트가 서버를 통해 실시간으로 메시지를 주고받을 수 있는 1:1 채팅 프로그램을 구현한 프로젝트입니다.

기존 Echo Server에서는 하나의 실행 흐름에서 `send()`와 `recv()`가 순차적으로 실행되었습니다.

```text
send()
  ↓
recv()
  ↓
send()
  ↓
recv()
```

이 구조에서는 상대방이 메시지를 보내더라도 현재 실행 흐름이 `recv()`까지 도달하기 전에는 메시지를 받을 수 없었습니다.

이를 해결하기 위해 `std::thread`를 사용하여 송신과 수신을 독립적인 실행 흐름으로 분리하였습니다.

또한 서버가 두 클라이언트의 연결을 각각 관리하고, 한 클라이언트에서 받은 메시지를 다른 클라이언트에게 전달하도록 구현하였습니다.

---

## 시스템 구조

```text
                    Server
              ┌─────────────────┐
              │   serverSocket  │
              │  연결 요청 대기  │
              └────────┬────────┘
                       │
              ┌────────┴────────┐
              │                 │
              ▼                 ▼
       clientSocket1      clientSocket2
              │                 │
              │                 │
          Client 1           Client 2
```

서버는 serverSocket을 사용하여 새로운 클라이언트 연결을 기다립니다.

클라이언트가 연결되면 `accept()`를 통해 해당 클라이언트와 실제 통신하는 clientSocket을 생성합니다.

이번 프로젝트에서는 두 개의 클라이언트를 연결하므로 서버는 clientSocket1, clientSocket2를 각각 관리합니다.

---

## 메세지 전달 방법

Client 1 → Server → Client 2
Client 2 → Server → Client 1

---

## 개발 환경
C++
Winsock2
std::thread
Visual Studio Code
MinGW-w64
Windows

---

## 프로젝트 구조
network-thread-chat/
├── client/
│   └── client.cpp
├── server/
│   └── server.cpp
└── README.md

---

# 실행 방법

g++ server/server.cpp -lws2_32 -o server/server.exe
.\server\server.exe

g++ client/client.cpp -lws2_32 -o client/client.exe
.\client\client.exe



