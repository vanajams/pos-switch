#pragma once

#include "fraud_rule.h"

class AmountRule : public FraudRule {
private:
    int threshold;

public:
    explicit AmountRule(int thresholdAmount)
        : threshold(thresholdAmount) {}

    bool isFraud(const IsoMessage& msg) const override {
        try {
            int amount = std::stoi(msg.getField(4));
            return amount > threshold;
        } catch (...) {
            return false;
        }
    }
};