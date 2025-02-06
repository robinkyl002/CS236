#pragma once
#include "Parser.h"
#include "Token.h"

class Rule {
    private: 
    Predicate headPredicate;
    vector<Predicate> predicateList;
    
    public:
    Rule() {}
    
    
}