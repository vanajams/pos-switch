#ifndef ISO_MESSAGE_H
#define ISO_MESSAGE_H
#include<iostream>
#include<vector>
#include<map>


using namespace std;

class IsoMessage{
    private:
    string mti;
    map<int, string> fields;

    public:
    void setField(int field, const string& value);
    string getField(int field) const;

};
#endif