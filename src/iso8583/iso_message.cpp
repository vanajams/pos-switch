#include "iso8583/iso_message.h"

void IsoMessage::setField(int field, const std::string& value) {
    fields[field] = value;
    bitmap.set(field - 1);
}

std::string IsoMessage::getField(int field) const {
    return fields.at(field);
}