#ifndef ISO_PARSER_H
#define ISO_PARSER_H

#include<iostream>
#include "iso_message.h"

using namespace std;

class IsoParse{

    public:

    IsoMessage parse(const string& raw);
    string build(const IsoMessage& msg);
};
#endif