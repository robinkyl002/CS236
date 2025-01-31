#pragma once
#include "Token.h"
#include "FiniteStateMachines.h"
#include <string>
#include <sstream>
#include <cctype>
#include <vector>

using namespace std;

class Scanner
{
private:
    string input;
    int line;
    int length;
    vector<Token> allTokens;

public:
    Scanner(const string &input) : input(input)
    {
        line = 1;
    }
    Token scanToken()
    {
    
        Token token = Token(UNDEFINED, "", line);
        FiniteStateMachines fsm = FiniteStateMachines(input);

        TokenType type = fsm.findTokenType();
        length = fsm.getTokenLength();
        line = line + fsm.getNewLines();
        string output = "";

        /*
        while the first character in the input is whitespace,
        create substring starting with the second character
        */
        switch (type)
        {

        case COMMA:
            input = input.substr(1);
            return Token(COMMA, ",", line);
        case PERIOD:
            input = input.substr(1);
            return Token(PERIOD, ".", line);
        case Q_MARK:
            input = input.substr(1);
            return Token(Q_MARK, "?", line);
        case LEFT_PAREN:
            input = input.substr(1);
            return Token(LEFT_PAREN, "(", line);
        case RIGHT_PAREN:
            input = input.substr(1);
            return Token(RIGHT_PAREN, ")", line);
        case COLON:
            input = input.substr(1);
            return Token(COLON, ":", line);
        case COLON_DASH:
            input = input.substr(2);
            return Token(COLON_DASH, ":-", line);
        case MULTIPLY:
            input = input.substr(1);
            return Token(MULTIPLY, "*", line);
        case ADD:
            input = input.substr(1);
            return Token(ADD, "+", line);
        case STRING:
            output = input.substr(0, length);
            input = input.substr(length);
            return Token(STRING, output, (line-fsm.getNewLines()));
        case SCHEMES:
            input = input.substr(7);
            return Token(SCHEMES, "Schemes", line);
        case FACTS:
            input = input.substr(5);
            return Token(FACTS, "Facts", line);
        case RULES:
            input = input.substr(5);
            return Token(RULES, "Rules", line);
        case QUERIES:
            input = input.substr(7);
            return Token(QUERIES, "Queries", line);
        case ID:
            output = input.substr(0, length);
            input = input.substr(length);
            return Token(ID, output, line);
        case COMMENT:
            output = input.substr(0, length);
            input = input.substr(length);
            return Token(COMMENT, output, line);
        case UNDEFINED:
            output = input.substr(0, length);
            input = input.substr(length);
            return Token(UNDEFINED, output, (line-fsm.getNewLines()));

        default:
            input = input.substr(1);
            return Token(UNDEFINED, to_string(input.at(0)), line);
        }

        return token;
    }


    vector<Token> scanAllTokens()
    {

        while (!input.empty())
        {
            while (isspace(input.at(0)))
            {
                if (input.at(0) == '\n')
                {
                    line++;
                }
                input = input.substr(1);
//                cout << input << endl;
//                cout << "Line: " << line << endl;
//                cout << endl;
                if (input.empty())
                {
                    allTokens.push_back(Token(END, "", line));
                    return allTokens;
                }
            }
            allTokens.push_back(scanToken());
        }
        allTokens.push_back(Token(END, "", line));
        return allTokens;
    }

    void stringifyTokens()
    {
        for (Token token : allTokens)
        {
            cout << token.toString() << endl;
        }
        cout << "Total Tokens = " << allTokens.size() << endl;
    }
};