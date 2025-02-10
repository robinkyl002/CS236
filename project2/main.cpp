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

    //    cout << input << endl;

    Scanner s = Scanner(input);

    //    Scanner s = Scanner("\n"
    //                        "\n"
    //                        "# unterminated string\n"
    //                        "\n"
    //                        "Schemes:\n"
    //                        "student(Name, ID, Address, Major)\n"
    //                        "\n"
    //                        "Facts:\n"
    //                        "student(North, '51, Main, CS).\n"
    //                        "\n"
    //                        "Rules:\n"
    //                        "major(Name,Major):-student(Name,ID,Address,Major).\n"
    //                        "\n"
    //                        "Queries:\n"
    //                        "major(North,Major)?\n"
    //                        "major(Name,MATH)?\n"
    //                        "\n"
    //                        "");

    tokens = s.scanAllTokens();

    // s.stringifyTokens();

    // cout << endl;
    // cout << endl;

    Parser p = Parser(tokens);

    p.parser();

    return 0;
}