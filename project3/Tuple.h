#pragma once
#include "Scheme.h"

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Tuple : public vector<string>
{

public:
    Tuple(vector<string> values) : vector<string>(values) {}

    string toString(const Scheme &scheme) const
    {
        const Tuple &tuple = *this;
        stringstream out;
        for (int i = 0; i < scheme.size(); i++)
        {
            if (i != scheme.size() - 1)
            {
                out << scheme.at(i);
                out << "=";
                out << tuple.at(i);
                out << ", ";
            }
            else
            {
                out << scheme.at(i);
                out << "=";
                out << tuple.at(i);
            }
        }
        return out.str();
    }
};
