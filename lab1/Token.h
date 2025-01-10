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
    Token(TokenType type, string value, int line) : type(type), value(value), line(line) {}

    string toString() const
    {
        stringstream out;
        out << "(" << type << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }
};