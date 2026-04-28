#include "router/router.h"
#include <unordered_map>

std::string Router::route(const IsoMessage& msg) {
    static const std::unordered_map<std::string, std::string> binRouting = {
        {"4", "VISA_ISSUER"},
        {"5", "MASTERCARD_ISSUER"},
        {"6", "RUPAY_ISSUER"}
    };

    try {
        std::string pan = msg.getField(2);

        if (pan.empty()) return "UNKNOWN";

        std::string network = pan.substr(0, 1);

        auto it = binRouting.find(network);
        if (it != binRouting.end()) {
            return it->second;
        }

        return "DEFAULT_ISSUER";

    } catch (...) {
        return "ERROR";
    }
}