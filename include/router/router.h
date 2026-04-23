#ifndef ROUTER_H
#define ROUTER_H

#include<iostream>
#include "iso_message.h"

using namespace std;

class Router{
    public:
    string route(const ISoMessage& msg);
};
#endif