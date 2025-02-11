#pragma once
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include <iostream>
#include <vector>

using namespace std;

class Parser
{
private:
    vector<Token> tokens;
    string name;
    vector<Parameter> parameters;
    vector<Parameter> domain;
    DatalogProgram dp = DatalogProgram();


public:
    Parser(const vector<Token> &tokens) : tokens(tokens), name(""), parameters(), domain() {}

    void datalogProgram()
    {
        match(SCHEMES);
        match(COLON);

        scheme();
        schemeList();

        match(FACTS);
        match(COLON);

        factList();

        match(RULES);
        match(COLON);

        ruleList();

        match(QUERIES);
        match(COLON);

        query();
        queryList();

        match(END);

        cout << dp.toString();
    }

    TokenType tokenType() const
    {
        return tokens.at(0).getType();
    }

    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }

//    void throwError()
//    {
//        cout << "error" << endl;
//    }

    /*
    checks to see whether TokenType entered matches current token
    prints out what token it is trying to match with, then advances token if it matches
    error is thrown if the type doesn't match, and advanceToken is not called
    */
    void match(TokenType t)
    {
        //        cout << "match: " << t << endl;

        try
        {
            if (tokenType() == t)
            {
                // TODO: add code to make it add Token to correct list
                if (name == "" && t == ID) {
                    name = tokens.at(0).getValue();
                } else if(name != "" && t == ID) {
                    parameters.push_back(Parameter(tokens.at(0)));
                }
                advanceToken();
            }
            else
            {
                throw tokens.at(0);
            }
        }
        catch (Token wrongToken)
        {
            cout << "Failure !" << endl;
            cout << "  " << wrongToken.toString();

            exit(0);
        }
    }

//    void schemeMatch(TokenType t) {
//        try
//        {
//            if (tokenType() == t)
//            {
//                // TODO: add code to make it add Token to correct list
//                if (name == "") {
//                    name = tokens.at(0).getValue();
//                } else if(name != "" && t == ID) {
//                    parameters.push_back(Parameter(tokens.at(0)));
//                }
//                advanceToken();
//            }
//            else
//            {
//                throw tokens.at(0);
//            }
//        }
//        catch (Token wrongToken)
//        {
//            cout << "Failure !" << endl;
//            cout << "  " << wrongToken.toString();
//
//            exit(0);
//        }
//    }

    void idList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(ID);
            idList();
        }
        else
        {
            // lambda
        }
    }

    void stringList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(STRING);
            stringList();
        }
        else
        {
            // lambda
        }
    }

    void scheme()
    {
        if (tokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
            dp.addScheme(Predicate(name, parameters));
            clear();
        }
        else
        {
            // lambda
        }
    }

    void schemeList()
    {
        if (tokenType() == ID)
        {
            scheme();
            schemeList();
        }
        else
        {
            // lambda
        }
    }

    void fact()
    {
        if (tokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            match(STRING);
            stringList();
            match(RIGHT_PAREN);
            match(PERIOD);
            dp.addFact(Predicate(name, parameters));
            clear();
        }
        else
        {
            // lambda
        }
    }

    void factList()
    {
        if (tokenType() == ID)
        {
            fact();
            factList();
        }
        else
        {
            // lambda
        }
    }

    void rule()
    {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }

    void ruleList()
    {
        if (tokenType() == ID)
        {
            rule();
            ruleList();
        }
        else
        {
            // lambda
        }
    }

    void headPredicate()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }

    void query()
    {
        if (tokenType() == ID)
        {
            predicate();
            match(Q_MARK);
        }
        else
        {
            // lambda
        }
    }

    void queryList()
    {
        if (tokenType() == ID)
        {
            query();
            queryList();
        }
        else
        {
            // lambda
        }
    }

    void predicate()
    {
        if (tokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            parameter();
            parameterList();
            match(RIGHT_PAREN);
        }
        else
        {
            // lambda
        }
    }

    void predicateList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            predicate();
            predicateList();
        }

        else
        {
            // lambda
        }
    }

    void parameterList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            parameter();
            parameterList();
        }

        else
        {
            // lambda
        }
    }

    void parameter()
    {
        if (tokenType() == STRING)
        {
            match(STRING);
        }
        else if (tokenType() == ID)
        {
            match(ID);
        }
        else
        {
            // lambda
        }
    }

    void clear() {
        name = "";
        while (!parameters.empty()) {
            parameters.pop_back();
        }
    }
};