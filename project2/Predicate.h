#pragma once
#include "Parser.h"
#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {
    private:
    string name;
    vector<Parameter> parameters;
    
    public:
    
    void predicate() {
    
    
    }
    
    void predicateList() {
        if (TokenType() == COMMA) {
            match(COMMA);
            predicate();
            predicateList();
        }
        else
        {
            //lambda
        }
        
    }
    
    void match(TokenType t) {
        cout << "match: " << t << endl;
        if (tokenType() == t) {
            //TODO: add code to make it add Token to correct list
            advanceToken();
        }
        else {
            throwError();
        }
}