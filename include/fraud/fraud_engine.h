#ifndef FRAUD_ENGINE_H
#define FRAUD_ENGINE_H

#include<iostream>
#include "iso_message.h"
using namespace std;

class fraudEngine{
    public:

    IsoMessage FraudEngine(const IsoMessage& msg);
};
#endif