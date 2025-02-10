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
        headPredicate.toString();
        cout << ":-";
        for (int i = 0; i < predicateList.size(); i++)
        {
            predicateList.at(i).toString();
        }
        cout << endl;
    }
};