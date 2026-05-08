#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iso8583/iso_parser.h"
#include "core/switch_core.h"
#include "gateway/tcp_server.h"
#include "utils/logger.h"

#pragma comment(lib, "ws2_32.lib")


void tcpServer::handleClient(SOCKET client_socket)
{
    try {
        char buffer[1024] = {0};

        int bytesReceived = ::recv(client_socket,
                                 buffer,
                                 sizeof(buffer),
                                 0);

        if (bytesReceived <= 0) {
            std::cout << "Client disconnected\n";
            closesocket(client_socket);
            return;
        }

        std::cout << "Received: " << buffer << std::endl;

        IsoParser parser;
        SwitchCore core;

        auto request = parser.parse(buffer);

        auto response = core.handleTransaction(request);

        auto rawResponse = parser.build(response);

        ::send(client_socket,
             rawResponse.c_str(),
             rawResponse.size(),
             0);

        std::cout << "Response sent\n";

    } catch (const std::exception& ex) {

        std::cout << "Error: " << ex.what() << std::endl;

    } catch (...) {

        std::cout << "Unknown error\n";
    }

    closesocket(client_socket);
}


void tcpServer::start()
{
    WSADATA wsaData;
    
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cout << "WSAStartup failed\n";
        return;
    }
    

    SOCKET server_fd = socket(AF_INET,
                              SOCK_STREAM,
                              IPPROTO_TCP);

    if (server_fd == INVALID_SOCKET) {
        std::cout << "Socket creation failed\n";
        return;
    }
    Logger logger("TCP Server Started");

    sockaddr_in address{};

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (::bind(server_fd, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cout << "Bind failed: " << WSAGetLastError() << std::endl;
        logger.error("Socket bind failed");
        return;
    }
    
    if (::listen(server_fd, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "Listen failed\n";
        return;
    }

    std::cout << "Server listening on port "<< port << std::endl;
     

    while (true)
    {
        std::cout << "Waiting for connection..."<< std::endl;
        logger.info("Waiting for client connection");
        SOCKET client_socket =
            ::accept(server_fd, nullptr, nullptr);

        if (client_socket == INVALID_SOCKET)
        {
            std::cout << "Accept failed\n";
            logger.error("Client accept failed");
            continue;
        }

        std::cout << "Client connected\n";

        pool.submit([this, client_socket]() {
            handleClient(client_socket);
        });
    }

    closesocket(server_fd);

    WSACleanup();
}

/*
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
*/