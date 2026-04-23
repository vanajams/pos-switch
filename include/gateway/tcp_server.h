#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include<iostream>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

class tcpServer{

    public:

    tcpServer(int p):port(p){}
};
#endif