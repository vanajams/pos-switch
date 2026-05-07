#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "iso8583/iso_message.h"
#include "iso8583/iso_parser.h"

#pragma comment(lib, "Ws2_32.lib")

int main() {
    // 1. Initialize Winsock
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    // 2. Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    // 3. Setup server address
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 4. Connect
    cout << "Trying to connect..." << endl;
    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Connection failed\n";
        return 1;
    }

    std::cout << "Connected to server\n";

    // 5. Build ISO Message using your class
    IsoMessage msg;
    msg.mti = "0200";
    msg.setField(2, "1234567890123456");
    msg.setField(4, "1000");

    cout<<"MTI is : " <<msg.mti<<endl;

    // 6. Convert to raw string using parser
    IsoParser parser;
    std::string isoRequest = parser.build(msg);

    std::cout << "Sending: " << isoRequest << std::endl;

    // 7. Send
   
    send(sock, isoRequest.c_str(), isoRequest.size(), 0);

    // 8. Receive
    char buffer[1024] = {0};
    int bytes = recv(sock, buffer, 1024, 0);

    std::cout << "Bytes received: " << bytes << std::endl;

    if (bytes > 0) {
        std::string responseStr(buffer, bytes);

        std::cout << "Raw Response: " << responseStr << std::endl;

        // 9. Parse response
        IsoMessage response = parser.parse(responseStr);

        std::cout << "Response MTI: " << response.mti << std::endl;
        std::cout << "Response Code (39): " << response.getField(39) << std::endl;
    } else {
        std::cout << "No response received\n";
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}