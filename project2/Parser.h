#pragma once
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
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
        if (tokenType() == t) {
            advanceToken();
        }
        else {
            throwError();
        }
    }
    
    void idList () {
        if(tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        }
        else {
            //lambda
        }
    }
    
    void stringList() {
        if (tokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            stringList();
        }
        else {
            // lambda
        }
    }
    
    void scheme() {
        if (tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
        else {
            //lambda
        }
    }
    
    void fact() {
        if (tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(STRING);
            stringList();
            match(RIGHT_PAREN);
            match(PERIOD);
        }
        else {
            //lambda
        }
    }
    
    
};