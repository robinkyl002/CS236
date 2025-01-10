#pragma once
#include <string>
#include <sstream>

using namespace std;

enum TokenType
{
    COMMA,
    PERIOD,
};

class Token
{
private:
    TokenType type;
    string value;
    int line;

public:
    Token(TokenType type) : type(type) {}

    string toString() const
    {
        stringstream out;
        out << "(" << type << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }
};