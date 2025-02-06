#pragma once
#include "Token.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>

using namespace std;

class DatalogProgram {
    private: 
    vector<Token> tokens;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    
    public:
    void datalogProgram () {}
}