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
                            "# simple two-var selects\n"
                            "\n"
                            "\n"
                            "Schemes:\n"
                            "\n"
                            "  b(x,y)\n"
                            "  c(x,y,z)\n"
                            "\n"
                            "Facts:\n"
                            "\n"
                            "  b('1','2').\n"
                            "  b('2','2').\n"
                            "  b('2','1').\n"
                            "  b('1','1').\n"
                            "\n"
                            "  c('2','2','2').\n"
                            "  c('4','2','1').\n"
                            "  c('1','2','4').\n"
                            "  c('1','1','2').\n"
                            "  c('2','4','4').\n"
                            "\n"
                            "Rules:\n"
                            "\n"
                            "Queries:\n"
                            "\n"
                            "  b(x,x)?\n"
                            "\n"
                            "  c(y,y,z)?\n"
                            "  c(x,y,x)?\n"
                            "  c(x,z,z)?\n"
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