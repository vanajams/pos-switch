#include "issuer/issuer_simulator.h"

IsoMessage IssuerSimulator::process(const IsoMessage& request) {
    IsoMessage response;
    response.mti = "0210"; // response MTI

    // Simple approval logic
    response.setField(39, "00"); // Approved

    return response;
}
