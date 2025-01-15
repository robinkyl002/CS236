#include <iostream>

#include "Token.h"
#include "Scanner.h"

using namespace std;

int main()
{
    Scanner s = Scanner("   .", 4);
    Token t = s.scanToken();
    cout << t.toString() << endl;

    return 0;
}