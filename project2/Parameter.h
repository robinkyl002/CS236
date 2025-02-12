#pragma once
#include "Token.h"
#include <string>

using namespace std;

class Parameter
{
private:
    string value;

public:
    Parameter(string value) : value(value) {}

    string toString()
    {
        return value;
    }
};