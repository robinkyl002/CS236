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
    // int tokens;
    vector<Token> allTokens;

public:
    Scanner(const string &input) : input(input)
    {
        // tokens = 0;
        line = 1;
    }
    Token scanToken()
    {
    
        Token token = Token(UNDEFINED, "", line);
        FiniteStateMachines fsm = FiniteStateMachines(input);

        TokenType type = fsm.findTokenType();
        length = fsm.getTokenLength();
        line = fsm.getNewLines();
        string output = "";

        /*
        while the first character in the input is whitespace,
        create substring starting with the second character
        */
        switch (type)
        {

        case COMMA:
            updateInputString();
            return Token(COMMA, ",", line);
        case PERIOD:
            updateInputString();
            return Token(PERIOD, ".", line);
        case Q_MARK:
            updateInputString();
            return Token(Q_MARK, "?", line);
        case LEFT_PAREN:
            updateInputString();
            return Token(LEFT_PAREN, "(", line);
        case RIGHT_PAREN:
            updateInputString();
            return Token(RIGHT_PAREN, ")", line);
        case COLON:
            updateInputString();
            return Token(COLON, ":", line);
        case COLON_DASH:
            updateInputString();
            return Token(COLON_DASH, ":-", line);
        case MULTIPLY:
            updateInputString();
            return Token(MULTIPLY, "*", line);
        case ADD:
            updateInputString();
            return Token(ADD, "+", line);
            // case '\n':
            //     line++;
        case STRING:
            output = input.substr(0, length);
            updateInputString();
            return Token(STRING, output, line);
        case SCHEMES:
            updateInputString();
            return Token(SCHEMES, "Schemes", line);
        case FACTS:
            updateInputString();
            return Token(FACTS, "Facts", line);
        case RULES:
            updateInputString();
            return Token(RULES, "Rules", line);
        case QUERIES:
            updateInputString();
            return Token(QUERIES, "Queries", line);
        case ID:
            output = input.substr(0, length);
            updateInputString();
            return Token(ID, output, line);
        case COMMENT:
            output = input.substr(0, length);
            updateInputString();
            return Token(COMMENT, output, line);
        case UNDEFINED:
            output = input.substr(0, length);
            updateInputString();
            return Token(UNDEFINED, output, line);

        default:
            input = input.substr(1);
            return Token(UNDEFINED, to_string(input.at(0)), line);
        }

        return token;
    }

    void updateInputString()
    {
        input = input.substr(length);
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
                if (input.size() == 0)
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

    // void setLength()
    // {
    //     length++;
    // }
};