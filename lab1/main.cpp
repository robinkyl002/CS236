#include <iostream>

#include "Token.h"

using namespace std;

int main()
{
    Token t = Token(COMMA, ",", 2);
    cout << t.toString() << endl;

    return 0;
}