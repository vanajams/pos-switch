#include "issuer/issuer_simulator.h"
#include<iostream>

IsoMessage IssuerSimulator::process(const IsoMessage& request) {
    IsoMessage response;
    response.mti = "0210"; // response MTI

    // Simple approval logic
    response.setField(39, "00"); // Approved

    std::cout<<"Response : "<<response.mti <<"  "<<response.bitmap <<std::endl;

    return response;
}
