#include "iso8583/field_definitions.h"

// Actual DEFINITION here
std::unordered_map<int, FieldDef> fieldDefs = {
    {2, {19, true, 2}},   // PAN
    {4, {12, false, 0}},  // Amount
    {7, {10, false, 0}}   // Transmission time
};