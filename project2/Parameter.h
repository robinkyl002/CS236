#pragma once
#include "Token.h"
#include <string>

using namespace std;

class Parameter
{
private:
    Token token;
    string parameterName;

public:
    Parameter(Token token) : token(token), parameterName(token.getValue()) {}

    string toString()
    {
        return parameterName;
    }
};