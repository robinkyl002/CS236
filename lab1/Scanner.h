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
        TokenType type = COMMA;
        string value = ",";
        int line = 4;
        return Token(type, value, line);

        /*
        while the first character in the input is whitespace,
        create substring starting with the second character
        */
        while (isspace(input.at(0)))
        {
            input = input.substr(1);
        }
    }
};