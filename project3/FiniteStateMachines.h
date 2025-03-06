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
    int tokenLength = 0;
    int location = 0;
    int charCount = 0;
    int idCount = 0;
    int schemeCount = 0;
    int factCount = 0;
    int ruleCount = 0;
    int queryCount = 0;
    int line = 0;

public:
    FiniteStateMachines(string input) : input(input) {}

    int singleCharacterFSM (char inputChar) {
        if (input.at(0) == inputChar)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int commaFSM()
    {
        return singleCharacterFSM(',');
    }

    int periodFSM()
    {
        return singleCharacterFSM('.');
    }

    int q_MarkFSM()
    {
        return singleCharacterFSM('?');
    }

    int leftParenFSM()
    {
        return singleCharacterFSM('(');
    }

    int rightParenFSM()
    {
        return singleCharacterFSM(')');
    }

    int colonFSM()
    {
        return singleCharacterFSM(':');
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
        return singleCharacterFSM('*');
    }

    int addFSM()
    {
        return singleCharacterFSM('+');
    }

    int schemesFSM()
    {
        return keywordFSM("Schemes");
    }

    int queriesFSM()
    {
        return keywordFSM("Queries");
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
        if (isalpha(input.at(location)))
        {
            for (int i = 0; i < expected.size(); i++)
            {
                if (input.at(i) == expected.at(i))
                {
                    charCount++;
                }
                else
                {
                    return 0;
                }
            }
        }
        return charCount;
    }

    int idFSM()
    {
        location = 0;
        idCount = 0;

        if (isalpha(input.at(location))) {

            location++;
            idCount++;

            while ( (location < input.size()) && (isalpha(input.at(location)) || isdigit(input.at(location)))) {
                    idCount++;
                    if (location + 1 >= input.size()) {
                        return idCount;
                    }
                    else {
                        location++;
                    }
            }
            return idCount;
        }
        return idCount;
    }

    int undefinedFSM()
    {
        int tempLine = 0;
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
                if (input.at(location) == '\n') {
                    tempLine++;
                }
                if ((location + 1) >= input.size())
                {
                    line = tempLine;
                    return charCount;
                }
                else {
                    location++;
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
        }
        return charCount;
    }

    void newLineFSM(char inputChar)
    {
        if (inputChar == '\n')
        {
            line++;
        }
    }

    int stringFSM()
    {
        location = 0;
        charCount = 0;
        int tempLine = 0;

        if (input.at(location) == '\'')
        {
            charCount++;
            location++;

            while (input.at(location) != '\'')
            {
                charCount++;
                
                if (input.at(location) == '\n') {
                    tempLine++;
                }
                if ((location + 1) >= input.size())
                {
                    return 0;
                }
                else {
                    location++;
                }
            }
            line = tempLine;
            charCount++;
        }
        return charCount;
    }

    TokenType findTokenType()
    {
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
       schemeCount = schemesFSM();
       queryCount = queriesFSM();
       factCount = factsFSM();
       ruleCount = rulesFSM();
        int comment = commentFSM();
       idCount = idFSM();
        int undefined = undefinedFSM();
        
        if (idCount == ruleCount || idCount == schemeCount || idCount == queryCount || idCount == factCount) {
                idCount = 0;
        }

        if (comma == 1 || period == 1 || q_mark == 1 || leftParen == 1 || rightParen == 1 || colon == 1 || multiply == 1 || add == 1 || idCount == 1) {
            undefined = 0;
        }

        TokenType type = UNDEFINED;

        map<TokenType, int> typeAndLength = {{COMMA, comma}, {PERIOD, period}, {Q_MARK, q_mark}, {LEFT_PAREN, leftParen}, {RIGHT_PAREN, rightParen}, {COLON, colon}, {COLON_DASH, colonDash}, {MULTIPLY, multiply}, {ADD, add}, {STRING, string}, {SCHEMES, schemeCount}, {QUERIES, queryCount}, {FACTS, factCount}, {RULES, ruleCount}, {COMMENT, comment}, {ID, idCount}, {UNDEFINED, undefined}};

        tokenLength = max({comma, period, q_mark, leftParen, rightParen, colon, colonDash, multiply, add, string, schemeCount, queryCount, factCount, ruleCount, comment, idCount, undefined});

        for (auto length : typeAndLength)
        {
            if (length.second == tokenLength)
            {
                type = length.first;
            }
        }
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