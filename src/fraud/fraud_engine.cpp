#include "fraud/fraud_engine.h"

void FraudEngine::addRule(std::unique_ptr<FraudRule> rule) {
    std::unique_lock lock(mutex_);
    rules.push_back(std::move(rule));
}

bool FraudEngine::checkFraud(const IsoMessage& msg) const {
    std::shared_lock lock(mutex_);

    for (const auto& rule : rules) {
        if (rule->isFraud(msg)) {
            return true;
        }
    }

    return false;
}