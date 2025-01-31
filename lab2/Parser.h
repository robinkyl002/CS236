#pragma once
#include "Token.h"
#include <vector>

class Parser {
    private:
    vector<Token> tokens;
    
    public:
    Parser (const vector<Token>& tokens) : tokens(tokens) {}
}