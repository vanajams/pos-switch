#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr*)&address, sizeof(address));

    listen(server_fd, 3);

    std::cout << "Server started...\n";

    SOCKET client_socket = accept(server_fd, nullptr, nullptr);

    char buffer[1024] = {0};
    recv(client_socket, buffer, 1024, 0);

    std::cout << "Received: " << buffer << std::endl;

    closesocket(client_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}