#pragma once

#include<iostream>
#include <vector>
#include <memory>
#include <shared_mutex>
#include "fraud_rule.h"

class FraudEngine {
private:
    std::vector<std::unique_ptr<FraudRule>> rules;
    mutable std::shared_mutex mutex_;

public:
    void addRule(std::unique_ptr<FraudRule> rule);

    bool checkFraud(const IsoMessage& msg) const;
};
