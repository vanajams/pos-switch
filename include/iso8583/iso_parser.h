#pragma once
#include <string>
#include <unordered_map>
#include "iso8583/iso_message.h"

using namespace std;

struct FieldDef {
    int length;
    bool isVariable;
    int varLengthDigits; // 2 for LLVAR, 3 for LLLVAR
};

std::unordered_map<int, FieldDef> fieldDefs = {
    {2, {19, true, 2}},   // PAN (LLVAR)
    {4, {12, false, 0}},  // Amount
    {7, {10, false, 0}},  // Transmission time
};

class IsoParser{

    public:

    IsoMessage parse(const string& raw);
    string build(const IsoMessage& msg);
};