#pragma once

#include "Token.h"
#include "Scanner.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class FiniteStateMachines
{
private:
    string input;
    int tokenLength;
    int location;
    int charCount;
    int line = 1;

public:
    FiniteStateMachines(const string input) : input(input) {}

    int commaFSM()
    {
        if (input.at(0) == ',')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int periodFSM()
    {
        if (input.at(0) == '.')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int q_MarkFSM()
    {
        if (input.at(0) == '?')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int leftParenFSM()
    {
        if (input.at(0) == '(')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int rightParenFSM()
    {
        if (input.at(0) == ')')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int colonFSM()
    {
        if (input.at(0) == ':')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int colonDashFSM()
    {
        if (input.at(0) == ':')
        {
            if (input.at(1) == '-')
            {
                return 2;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }

    int multiplyFSM()
    {
        if (input.at(0) == '*')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int addFSM()
    {
        if (input.at(0) == '+')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int schemesFSM()
    {
        return keywordFSM("Facts");
    }

    int queriesFSM()
    {
        return keywordFSM("Facts");
    }

    int rulesFSM()
    {
        return keywordFSM("Rules");
    }

    int factsFSM()
    {
        return keywordFSM("Facts");
    }

    int keywordFSM(string expected)
    {
        charCount = 0;
        location = 0;
        string correctString = expected;
        bool matches = true;
        if (isalpha(input.at(location)))
        {

            while (matches)
            {
                if (input.at(location) == correctString.at(location))
                {
                    charCount++;
                }
                else
                {
                    matches = false;
                }
            }
        }
        return charCount;
    }

    int idFSM()
    {
        location = 0;
        charCount = 0;

        if (isalpha(input.at(location)))
        {
            while (isalpha(input.at(location)))
            {
                charCount++;
                location++;
            }
            return charCount;
        }
        else
        {
            return 0;
        }
    }

    int undefinedFSM()
    {
        // number
        if (isdigit(input.at(0)))
        {
            return 1;
        }
        // string not terminated
        else if (input.at(location) == '\'')
        {
            charCount++;
            location++;

            while (input.at(location) != '\'')
            {
                charCount++;
                location++;
                newLineFSM(location);
                if (location >= input.size())
                {
                    return charCount;
                }
            }
            return 0;
        }
        else
        {
            return 1;
        }
    }

    int commentFSM()
    {
        charCount = 0;
        location = 0;

        if (input.at(0) == '#')
        {
            charCount++;
            location++;
            while (input.at(location) != '\n')
            {
                charCount++;
                location++;
            }
            newLineFSM(location);
        }
        return charCount;
    }

    void newLineFSM(char input)
    {
        if (input == '\n')
        {
            line++;
        }
    }

    int stringFSM()
    {
        location = 0;
        charCount = 0;

        if (input.at(location) == '\'')
        {
            charCount++;
            location++;

            while (input.at(location) != '\'')
            {
                charCount++;
                location++;
                newLineFSM(location);
                if (location >= input.size())
                {
                    return 0;
                }
            }
            charCount++;
        }
        return charCount;
    }

    TokenType findTokenType()
    {
        newLineFSM(input.at(0));
        int comma = commaFSM();
        int period = periodFSM();
        int q_mark = q_MarkFSM();
        int leftParen = leftParenFSM();
        int rightParen = rightParenFSM();
        int colon = colonFSM();
        int colonDash = colonDashFSM();
        int multiply = multiplyFSM();
        int add = addFSM();
        int string = stringFSM();
        int schemes = schemesFSM();
        int queries = queriesFSM();
        int facts = factsFSM();
        int rules = rulesFSM();
        int comment = commentFSM();
        int id = idFSM();
        int undefined = undefinedFSM();

        TokenType type = UNDEFINED;

        map<TokenType, int> typeAndLength = {{COMMA, comma}, {PERIOD, period}, {Q_MARK, q_mark}, {LEFT_PAREN, leftParen}, {RIGHT_PAREN, rightParen}, {COLON, colon}, {COLON_DASH, colonDash}, {MULTIPLY, multiply}, {ADD, add}, {STRING, string}, {SCHEMES, schemes}, {QUERIES, queries}, {FACTS, facts}, {RULES, rules}, {COMMENT, comment}, {ID, id}, {UNDEFINED, undefined}};

        tokenLength = max({comma, period, q_mark, leftParen, rightParen, colon, colonDash, multiply, add, string, schemes, queries, facts, rules, comment, id, undefined});

        for (auto length : typeAndLength)
        {
            if (length.second == tokenLength)
            {
                type = length.first;
            }
        }
        cout << tokenLength << endl;
        return type;
    }

    int getTokenLength()
    {
        return tokenLength;
    }

    int getNewLines()
    {
        return line;
    }
};