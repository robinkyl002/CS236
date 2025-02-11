#pragma once
#include "Token.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <string>

using namespace std;

class DatalogProgram
{
private:
    vector<Token> tokens;
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    vector<Parameter> domain;

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

    vector<Parameter> getDomain() {
        return domain;
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

    void addDomainItem(Parameter newDomainItem) {
        domain.push_back(newDomainItem);
    }

    string toString() {
        string dp;

        dp = "Success!\nSchemes(" + to_string(schemes.size()) + "):\n";
        for (Predicate scheme : schemes) {
            dp.append("  " + scheme.toString() + "\n");
        }

        dp.append("Facts(" + to_string(facts.size()) + "):\n");

        for (Predicate fact : facts) {
            dp.append("  " + fact.toString() + ".\n");
        }

        dp.append("Rules(" + to_string(rules.size()) + "):\n");

        for (Rule rule : rules) {
            dp.append("  " + rule.toString() + ".\n");
        }

        dp.append("Queries(" + to_string(queries.size()) + "):\n");

        for (Predicate query : queries) {
            dp.append("  " + query.toString() + "?\n");
        }

        dp.append("Domain(" + to_string(domain.size()) + "):\n");

        for (Parameter item: domain) {
            dp.append("  " + item.toString() + "\n");
        }

        return dp;
    }
};