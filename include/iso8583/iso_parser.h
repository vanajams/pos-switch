#pragma once
#include <string>
#include "iso8583/iso_message.h"
#include "iso8583/field_definitions.h"
using namespace std;



class IsoParser{

    public:

    IsoMessage parse(const string& raw);
    string build(const IsoMessage& msg);
};