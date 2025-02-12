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

    ifstream in;
    in.open(argv[1]);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();

    Scanner s = Scanner(input);

//        Scanner s = Scanner("\n"
//                            "\n"
//                            "# small test with no syntax errors\n"
//                            "\n"
//                            "\n"
//                            "Schemes:\n"
//                            "\n"
//                            "  married(x,y)\n"
//                            "  child(x,y)\n"
//                            "\n"
//                            "Facts:\n"
//                            "\n"
//                            "  married('Jim', 'Bea').\n"
//                            "  child('Ned', 'Bea').\n"
//                            "\n"
//                            "Rules:\n"
//                            "\n"
//                            "  married(y,x) :- married(x,y).\n"
//                            "  child(x,z) :- child(x,y), married(y,z).\n"
//                            "\n"
//                            "Queries:\n"
//                            "\n"
//                            "  child('Ned', 'Jim')?\n"
//                            "\n"
//                            "");

    tokens = s.scanAllTokens();

    // s.stringifyTokens();

    // cout << endl;
    // cout << endl;

    Parser p = Parser(tokens);

    p.datalogProgram();

    return 0;
}