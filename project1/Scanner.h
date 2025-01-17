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
    int line;

public:
    Scanner(const string &input, int line) : input(input), line(line) {}
    Token scanToken()
    {
        // TokenType type = UNDEFINED;
        // string value = ",";
        Token token = Token(UNDEFINED, "", 0);

        /*
        while the first character in the input is whitespace,
        create substring starting with the second character
        */
        while (isspace(input.at(0)))
        {
            input = input.substr(1);
        }
        // if (input.at(0) == ',')
        // {
        //     return Token(COMMA, ",", line);
        // }
        switch (input.at(0))
        {
        case ',':
            return Token(COMMA, ",", line);
        case '.':
            return Token(PERIOD, ".", line);
        case '?':
            return Token(Q_MARK, "?", line);
        case '(':
            return Token(LEFT_PAREN, "(", line);
        case ')':
            return Token(RIGHT_PAREN, ")", line);
        case ':':
            return Token(COLON, ":", line);
        case ';':
            return Token(COLON_DASH, ";", line);
        case '*':
            return Token(MULTIPLY, "*", line);
        case '+':
            return Token(ADD, "+", line);
        }

        return token;
    }
};