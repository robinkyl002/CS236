#pragma once
#include "Token.h"
#include <iostream>
#include <vector>

using namespace std;

class Parser {
    private:
    vector<Token> tokens;
    
    public:
    Parser (const vector<Token>& tokens) : tokens(tokens) {}
    
    TokenType tokenType() const{
        return tokens.at(0).getType();
    }
    
    void advanceToken() {
        tokens.erase(tokens.begin());
    }
    
    void throwError() {
        cout << "error" << endl;
    }
    
    /*
    checks to see whether TokenType entered matches current token
    prints out what token it is trying to match with, then advances token if it matches
    error is thrown if the type doesn't match, and advanceToken is not called
    */
    void match(TokenType t) {
        cout << "match: " << t << endl;
        if (tokens.at(0).getType() == t) {
            advanceToken();
        }
        else {
            throwError();
        }
    }
};