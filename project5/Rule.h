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

    Rule(Predicate headPredicate) : headPredicate(headPredicate), predicateList() {}

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

    void addBodyPredicate(Predicate body) {
        predicateList.push_back(body);
    }

    vector<Predicate> getPredicateList() {
        return predicateList;
    }

    Predicate getHeadPredicate() {
        return headPredicate;
    }
};