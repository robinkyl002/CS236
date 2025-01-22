#include <iostream>
#include <fstream>

#include "Token.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream in;
    in.open(argv[1]);
    while (!in.eof())
    {
        Scanner s = Scanner("   .", 4);
        Token t = s.scanToken();
        cout << t.toString() << endl;
    }
    in.close();

    return 0;
}