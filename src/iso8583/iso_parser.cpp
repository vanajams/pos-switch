#include "iso8583/iso_parser.h"
#include <sstream>
#include<iostream>

/*
IsoMessage IsoParser::parse(const std::string& raw) {
    IsoMessage msg;

    int pos = 0;

    // MTI
    msg.mti = raw.substr(pos, 4);
    pos += 4;

    // Bitmap (16 hex chars → 64 bits)
    std::string bitmapHex = raw.substr(pos, 16);
    pos += 16;

    msg.bitmap = std::bitset<64>(std::stoull(bitmapHex, nullptr, 16));

    for (int i = 1; i <= 64; ++i) {
        if (msg.bitmap.test(i - 1)) {
            auto def = fieldDefs[i];

            if (def.isVariable) {
                int len = std::stoi(raw.substr(pos, def.varLengthDigits));
                pos += def.varLengthDigits;

                msg.setField(i, raw.substr(pos, len));
                pos += len;
            } else {
                msg.setField(i, raw.substr(pos, def.length));
                pos += def.length;
            }
        }
    }

    return msg;
}
*/

IsoMessage IsoParser::parse(const std::string& raw)
{
    IsoMessage msg;

    std::stringstream ss(raw);

    std::string token;

    // MTI
    getline(ss, token, '|');
    msg.mti = token;

    while (getline(ss, token, '|'))
    {
        auto pos = token.find('=');

        if (pos != std::string::npos)
        {
            int field =
                std::stoi(token.substr(0, pos));

            std::string value =
                token.substr(pos + 1);

            msg.setField(field, value);
        }
    }

    return msg;
}

std::string IsoParser::build(const IsoMessage& msg)
{
    std::stringstream ss;

    ss << msg.mti;

    for (const auto& field : msg.fields)
    {
        ss << "|"
           << field.first
           << "="
           << field.second;
    }

    return ss.str();
}
/*
std::string IsoParser::build(const IsoMessage& msg) {
    std::string raw;

    // 1. Add MTI
    raw += msg.mti;

    std::cout<<" raw message is : "<< raw<<endl;

    // 2. Add bitmap (convert to hex string)
    unsigned long long bitmapVal = msg.bitmap.to_ullong();
    std::stringstream ss;
    ss << std::hex << bitmapVal;
    raw += ss.str();

    // 3. Add fields (simple format for now)
    for (const auto& [field, value] : msg.fields) {
        raw += "|" + std::to_string(field) + "=" + value;
    }
    std::cout<<" Full raw message is : "<< raw<<endl;
    return raw;
}*/