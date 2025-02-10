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
        rule += ":-";
        for (int i = 0; i < predicateList.size(); i++)
        {
            rule += predicateList.at(i).toString();
        }

        return rule;
    }
};