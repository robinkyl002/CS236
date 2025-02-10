#pragma once
#include "Token.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>

using namespace std;

class DatalogProgram
{
private:
    vector<Token> tokens;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;

public:
    void datalogProgram() {}

    vector<Predicate> getSchemes()
    {
        return schemes;
    }

    vector<Predicate> getFacts()
    {
        return facts;
    }

    vector<Rule> getRules()
    {
        return rules;
    }

    vector<Predicate> getQueries()
    {
        return queries;
    }

    void addScheme(Predicate newScheme)
    {
        schemes.push_back(newScheme);
    }

    void addFact(Predicate newFact)
    {
        facts.push_back(newFact);
    }

    void addRule(Rule newRule)
    {
        rules.push_back(newRule);
    }

    void addQuery(Predicate newQuery)
    {
        queries.push_back(newQuery);
    }
};