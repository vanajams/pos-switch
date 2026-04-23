#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
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
        int serv_fd = socket(AF_INET, SOCK_STREAM,0);
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        bind(server_fd, (struct sockaddr*)* address, sizeof(address));
        listen(server_fd, 5);

        cout<<"Server listening on port "<<port<<endl;

        while(true)
        {
            int client_sock = accept(serv_fd, nullptr,nullptr);

            thread([client_sock]()) 
        }


    }
};