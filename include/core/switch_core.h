#ifndef SWITCH_CORE_H
#define SWITCH_CORE_H

#include<iostream>
#include "router.h"
#include "issuer_simulator.h"
#include "iso_message.h"

using namespace std;

class SwitchCore{
    private:
    Router router;
    IssuerSimulator issuer;

    public: 
    IsoMessage handleTransaction(const IsoMessage& request);
};
#endif