#pragma once
#include "Parser.h"
#include "Token.h"
#include "Predicate.h"

class Rule
{
private:
    Predicate headPredicate;
    vector<Predicate> predicateList;

public:
    Rule(Predicate headPredicate, vector<Predicate> predicateList) : headPredicate(headPredicate), predicateList(predicateList) {}

    string toString()
    {
        string rule;

        rule = headPredicate.toString();
        rule += " :- ";
        for (Predicate predicate : predicateList)
        {
            rule.append(predicate.toString() + ",");
        }

        rule.pop_back();
//        rule.pop_back();

        return rule;
    }

    void addPredicateToRule(Predicate listItem) {
        predicateList.push_back(listItem);
    }

    vector<Predicate> getPredicateList() {
        return predicateList;
    }
};