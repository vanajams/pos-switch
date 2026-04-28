#pragma once

#include <string>
#include "iso8583/iso_message.h"

class Router {
public:
    std::string route(const IsoMessage& msg);
};