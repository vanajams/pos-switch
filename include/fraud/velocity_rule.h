#pragma once

#include "fraud_rule.h"
#include <unordered_map>
#include <mutex>
#include <chrono>

class VelocityRule : public FraudRule {
private:
    mutable std::mutex mutex_;
    mutable std::unordered_map<std::string, int> txnCount;

    int threshold;

public:
    explicit VelocityRule(int threshold)
        : threshold(threshold) {}

    bool isFraud(const IsoMessage& msg) const override {
        std::lock_guard<std::mutex> lock(mutex_);

        std::string card = msg.getField(2); // PAN

        txnCount[card]++;

        return txnCount[card] > threshold;
    }
};