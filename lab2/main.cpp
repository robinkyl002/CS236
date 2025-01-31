#include "Token.h"
#include "Parser.h"
#include <iostream>

int main (int argc, char* argv[]) {
    
    vector<Token> tokens = {
    Token(ID,"Ned",2),
    Token(LEFT_PAREN,"(",2),
    Token(RIGHT_PAREN,")",2),
    };

    // Parser p = Parser(tokens);
    // cout << p.tokenType() << endl;
    // p.advanceToken();
    // cout << p.tokenType() << endl;
    // p.advanceToken();
    // cout << p.tokenType() << endl;
    // p.throwError();
    
    Parser p = Parser(tokens);
    p.match(ID);
    p.match(LEFT_PAREN);
    p.match(ID);         // intentional error
    p.match(RIGHT_PAREN);
    return 0;
}