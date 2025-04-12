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

    ifstream in;
    in.open(argv[1]);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();

    Scanner s = Scanner(input);

//        Scanner s = Scanner("\n"
//                            "\n"
//                            "# one, two, three param predicates, with vars, some renames\n"
//                            "\n"
//                            "\n"
//                            "Schemes:\n"
//                            "\n"
//                            "  a(x)\n"
//                            "  b(x,y)\n"
//                            "  c(x,y,z)\n"
//                            "\n"
//                            "Facts:\n"
//                            "\n"
//                            "  a('1').\n"
//                            "  a('4').\n"
//                            "  a('2').\n"
//                            "\n"
//                            "  b('1','2').\n"
//                            "  b('2','2').\n"
//                            "  b('2','1').\n"
//                            "\n"
//                            "  c('2','2','2').\n"
//                            "  c('4','2','1').\n"
//                            "  c('1','2','4').\n"
//                            "\n"
//                            "Rules:\n"
//                            "\n"
//                            "Queries:\n"
//                            "\n"
//                            "  a(x)?\n"
//                            "\n"
//                            "  b(x,y)?\n"
//                            "  b(x,'2')?\n"
//                            "  b(x,'4')?\n"
//                            "  b('2',y)?\n"
//                            "  b('4',y)?\n"
//                            "\n"
//                            "  c(x,y,z)?\n"
//                            "  c(x,y,'2')?\n"
//                            "  c(x,'1',z)?\n"
//                            "  c(x,'2',z)?\n"
//                            "  c('4',y,z)?\n"
//                            "  c('4','2',z)?\n"
//                            "\n"
//                            "  a(a)?\n"
//                            "  b(a,b)?\n"
//                            "  c(a,b,c)?\n"
//                            "\n"
//                            "");

    tokens = s.scanAllTokens();

    // s.stringifyTokens();

    Parser p = Parser(tokens);

    Interpreter interpreter = Interpreter(p.datalogProgram());

//    interpreter.print();

    interpreter.interpret();

    return 0;
}