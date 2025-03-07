#include <iostream>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<Token> tokens;

//    ifstream in;
//    in.open(argv[1]);
//    stringstream ss;
//    ss << in.rdbuf();
//    string input = ss.str();
//    in.close();
//
//    Scanner s = Scanner(input);

        Scanner s = Scanner("\n"
                            "\n"
                            "# single params, only constants\n"
                            "\n"
                            "\n"
                            "Schemes:\n"
                            "\n"
                            "A(X)\n"
                            "B(Y)\n"
                            "C(Z)\n"
                            "\n"
                            "Facts:\n"
                            "\n"
                            "A('1').\n"
                            "A('2').\n"
                            "\n"
                            "B('2').\n"
                            "B('3').\n"
                            "\n"
                            "C('').\n"
                            "C('4').\n"
                            "\n"
                            "Rules:\n"
                            "\n"
                            "Queries:\n"
                            "\n"
                            "A('2')?\n"
                            "B('4')?\n"
                            "C('')?\n"
                            "\n"
                            "");

    tokens = s.scanAllTokens();

    // s.stringifyTokens();

    // cout << endl;
    // cout << endl;

    Parser p = Parser(tokens);

    Interpreter interpreter = Interpreter(p.datalogProgram());

//    interpreter.print();

    interpreter.interpret();

    return 0;
}