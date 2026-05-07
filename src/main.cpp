#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "gateway/tcp_server.h"

#pragma comment(lib, "Ws2_32.lib")

int main() {
   
    tcpServer server(8080);
    server.start();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
    return 0;

    
}