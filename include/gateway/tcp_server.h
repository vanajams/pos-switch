#pragma once

#include<iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "concurrency/thread_pool.h"
using namespace std;
#pragma comment(lib, "ws2_32.lib")



class tcpServer {
private:
    int port;
    ThreadPool pool;

public:
    //explicit TcpServer(int p);
    tcpServer(int p)
    : port(p),
      pool(std::thread::hardware_concurrency())
{
}
    void start();

    void handleClient(SOCKET client_socket);
    
    
};
/*
class tcpServer{

    private:
        int port;
    public:
    

    tcpServer(int p):port(p){};
    void start();
    
    void tcpServer::handleClient(SOCKET client_socket){}
};*/