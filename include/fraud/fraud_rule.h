#pragma once

#include "iso8583/iso_message.h"

class FraudRule {
public:
    virtual ~FraudRule() = default;

    virtual bool isFraud(const IsoMessage& msg) const = 0;
};