#pragma once
#include "Scheme.h"

#include <vector>
#include <string>

class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        out << scheme.size();
        out << scheme.at(0);
        out << tuple.size();
        out << tuple.at(0);
        return out.str();
    }

};
