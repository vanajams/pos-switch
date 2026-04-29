#include "core/switch_core.h"

IsoMessage SwitchCore::handleTransaction(const IsoMessage& request) {

    // Routing decision
    std::string routeTo = router.route(request);

    IsoMessage response;

    // Fraud check
    if (fraudEngine.checkFraud(request)) {
        response.mti = "0210";
        response.setField(39, "05"); // Declined
        return response;
    }

    // Process via issuer
    response = issuer.process(request);

    return response;
}