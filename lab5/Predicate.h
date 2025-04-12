#pragma once
#include "Parser.h"
#include "Parameter.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Predicate
{
private:
    string name;
    vector<Parameter> parameters;

public:
    Predicate(string name, vector<Parameter> parameters) : name(name), parameters(parameters) {}

    Predicate(string name) : name(name), parameters() {}

    string toString()
    {
        string predicate;

        predicate = name + "(";

        for (int i = 0; i < parameters.size(); i++)
        {
            predicate += parameters.at(i).toString();

            if (i < parameters.size() - 1)
            {
                predicate += ",";
            }
            else
            {
                predicate += ")";
            }
        }

        if (parameters.empty()) {
            predicate += ")";
        }
        return predicate;
    }

    string getPredicateName() {
        return name;
    }

    vector<Parameter> getParameters() {
        return parameters;
    }
};