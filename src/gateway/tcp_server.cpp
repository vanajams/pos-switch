#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iso8583/iso_parser.h"
#include "core/switch_core.h"
#include "gateway/tcp_server.h"
#pragma comment(lib, "ws2_32.lib")

void tcpServer::start()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cout << "Winsock init failed\n";
        return;
    }
    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    //bind(server_fd, (sockaddr*)&address, sizeof(address));
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        return;
    }
    
    //listen(server_fd, 5);
    if (listen(server_fd, 5) == SOCKET_ERROR) {
        std::cout << "Listen failed\n";
        return;
    }

    cout<<"Server listening on port "<<port<<endl;

    while (true) {
        cout << "Waiting for connection..." << endl;

        SOCKET client_socket = accept(server_fd, nullptr, nullptr);

        cout << "Client connected!" << endl;

       // SOCKET client_socket = accept(server_fd, nullptr, nullptr);

        std::thread([client_socket]() {
            char buffer[1024] = {0};
            recv(client_socket, buffer, 1024, 0);

            IsoParser parser;
            SwitchCore core;

            auto request = parser.parse(buffer);
            auto response = core.handleTransaction(request);

            auto rawResponse = parser.build(response);
            send(client_socket, rawResponse.c_str(), rawResponse.size(), 0);

            closesocket(client_socket);
        }).detach();
    }
    WSACleanup();

}
