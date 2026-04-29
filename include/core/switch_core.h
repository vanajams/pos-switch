#pragma once

#include "iso8583/iso_message.h"
#include "router/router.h"
#include "issuer/issuer_simulator.h"
#include "fraud/fraud_engine.h"

class SwitchCore {
private:
    Router router;
    IssuerSimulator issuer;
    FraudEngine fraudEngine;

public:
    IsoMessage handleTransaction(const IsoMessage& request);
};