#pragma once

#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

class tcpServer{

    private:
        int port;
    public:
    

    tcpServer(int p):port(p){};
    void start();
};
