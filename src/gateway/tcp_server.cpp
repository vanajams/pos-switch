#include <iostream>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "iso8583/iso_parser.h"
#include "core/switch_core.h"

using namespace std;

class TcpServer{

    private:
    int port;

    public:
    TcpServer(int p) : port(p){}
    
    void start()
    {
        SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        bind(server_fd, (sockaddr*)&address, sizeof(address));
        listen(server_fd, 5);

        cout<<"Server listening on port "<<port<<endl;

       while (true) {
            SOCKET client_socket = accept(server_fd, nullptr, nullptr);

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

    }
};