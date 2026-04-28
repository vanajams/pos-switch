#pragma once

#include<iostream>
#include "router/router.h"
#include "issuer/issuer_simulator.h"
#include "iso8583/iso_message.h"

using namespace std;

class SwitchCore{
    private:
    Router router;
    IssuerSimulator issuer;

    public: 
    IsoMessage handleTransaction(const IsoMessage& request);
};
