#include <iostream>
#include <fstream>
#include <vector>

#include "Token.h"
#include "Scanner.h"

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

//    ifstream in;
//    in.open(argv[1]);
//    stringstream ss;
//    ss << in.rdbuf();
//    string input = ss.str();
//    in.close();

    cout << input << endl;

    Scanner s = Scanner(input);

    tokens = s.scanAllTokens();

    s.stringifyTokens();

    return 0;
}