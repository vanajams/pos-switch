#include <iostream>
#include "core/switch_core.h"
#include "fraud/fraud_engine.h"

FraudEngine fraudEngine;

fraudEngine.addRule(std::make_unique<AmountRule>(100000));
fraudEngine.addRule(std::make_unique<VelocityRule>(5));

IsoMessage SwitchCore::handleTransaction(const IsoMessage& request) {
    std::string routeTo = router.route(request);
    IsoMessage response = issuer.process(request);
    // (Future: fraud check here)
     if (fraudEngine.checkFraud(request)) {
        response.mti = "0210";
        response.setField(39, "05"); // Decline
       
    }
    return response;
}
