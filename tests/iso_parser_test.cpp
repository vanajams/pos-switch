#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iso8583/iso_parser.h"
#include "core/switch_core.h"

int main() {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    std::string isoRequest = "0200|2=1234567890123456|4=1000";

    send(sock, isoRequest.c_str(), isoRequest.size(), 0);

    char buffer[1024] = {0};
    recv(sock, buffer, 1024, 0);

    std::cout << "Response: " << buffer << std::endl;

    return 0;
}
