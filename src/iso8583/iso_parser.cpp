#include "iso8583/iso_parser.h"

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