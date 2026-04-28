#pragma once

#include<iostream>
#include<vector>
#include<map>


using namespace std;


class IsoMessage{
   public:
    string mti;
    map<int, string> fields;

    
    void setField(int field, const string& value);
    string getField(int field) const;

};
