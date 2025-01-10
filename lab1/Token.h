#pragma once
#include <string>
#include <sstream>
#include <typeinfo>

using namespace std;

enum TokenType
{
    COMMA,
    PERIOD,
    STRING,
    NUMBER,
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
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    }

    string typeName(TokenType type) const
    {
        if (type == COMMA)
        {
            return "COMMA";
        }
        if (type == PERIOD)
        {
            return "PERIOD";
        }
    }
};