#pragma once
#include "Token.h"
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

class Scanner
{
private:
    string input;

public:
    Scanner(const string &input) : input(input) {}
    Token scanToken()
    {
        // TokenType type = UNDEFINED;
        // string value = ",";
        Token token = Token(UNDEFINED, "", 0);
        int line = 3;

        /*
        while the first character in the input is whitespace,
        create substring starting with the second character
        */
        while (isspace(input.at(0)))
        {
            input = input.substr(1);
        }
        if (input.at(0) == ',')
        {
            return Token(COMMA, ",", line);
        }

        return token;
    }
};