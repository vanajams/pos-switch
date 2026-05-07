#pragma once

#include <string>
#include <unordered_map>
#include <bitset>

class IsoMessage {
public:
    std::string mti;
    std::bitset<64> bitmap;
    std::unordered_map<int, std::string> fields;

    void setField(int field, const std::string& value);
    std::string getField(int field) const;
};