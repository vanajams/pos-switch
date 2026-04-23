#ifndef ISSUER_SIMULATOR_H
#define ISSUER_SIMULATOR_H

#include<iostream>
#include "iso_message.h"

using namespace std;

class IssuerSimulator{
    public:
    IsoMessage process(const IsoMessage& request);
};
#endif