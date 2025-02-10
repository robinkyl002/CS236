#pragma once
#include "Token.h"
#include <string>

using namespace std;

class Parameter
{
private:
    Token token;

public:
    Parameter(Token token) : token(token) {}

    string toString()
    {
        return token.getValue();
    }
};