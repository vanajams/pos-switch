#pragma once

#include <unordered_map>

struct FieldDef {
    int length;
    bool isVariable;
    int varLengthDigits;
};

// Only DECLARATION here
extern std::unordered_map<int, FieldDef> fieldDefs;