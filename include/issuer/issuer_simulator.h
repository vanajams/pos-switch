#pragma once

#include<iostream>
#include "iso8583/iso_message.h"

using namespace std;

class IssuerSimulator{
    public:
    IsoMessage process(const IsoMessage& request);
};