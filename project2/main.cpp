#include <iostream>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"

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
                            "# small test with no syntax errors\n"
                            "\n"
                            "\n"
                            "Schemes:\n"
                            "\n"
                            "  sister(x,y)\n"
                            "  parent(x,y)\n"
                            "  aunt(x,y)\n"
                            "\n"
                            "Facts:\n"
                            "\n"
                            "  sister('Ann', 'Bob').\n"
                            "  parent('Bob', 'Jay').\n"
                            "\n"
                            "Rules:\n"
                            "\n"
                            "  aunt(x,z) :- sister(x,y), parent(y,z).\n"
                            "\n"
                            "Queries:\n"
                            "\n"
                            "  aunt('Ann', 'Jay')?\n"
                            "\n"
                            "");

    tokens = s.scanAllTokens();

    // s.stringifyTokens();

    // cout << endl;
    // cout << endl;

    Parser p = Parser(tokens);

    p.datalogProgram();

    return 0;
}