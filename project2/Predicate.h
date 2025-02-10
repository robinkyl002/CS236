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

    // void predicate()
    // {
    // }

    // void predicateList()
    // {
    //     if (TokenType() == COMMA)
    //     {
    //         // match(COMMA);
    //         predicate();
    //         predicateList();
    //     }
    //     else
    //     {
    //         // lambda
    //     }
    // }

    // void match(TokenType t) {
    //     cout << "match: " << t << endl;
    //     if (tokenType() == t) {
    //         //TODO: add code to make it add Token to correct list
    //         advanceToken();
    //     }
    //     else {
    //         throwError();
    //     }
    // }

    string toString()
    {
        string predicate;

        predicate = name + "(";

        cout << name << "(";
        for (int i = 0; i < parameters.size(); i++)
        {
            predicate += parameters.at(i).toString();
            cout << parameters.at(i).toString();

            if (i < parameters.size() - 1)
            {
                predicate += ", ";

                cout << ", ";
            }
            else
            {
                predicate += ")";
                predicate += ".";

                cout << ")" << ".";
            }
        }

        cout << predicate << endl;

        return predicate;
    }
};