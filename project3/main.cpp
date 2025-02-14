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

//
// Created by Kyle Robinson on 2/12/25.
//
//#include "Tuple.h"
//#include "Scheme.h"
//#include "Relation.h"
//
//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//int main() {
//
//    vector<string> names = { "ID", "Name", "Major" };
//
//    Scheme scheme(names);
//
//    Relation relation("student", scheme);
//
//    vector<string> values[] = {
//            {"'42'", "'Ann'", "'CS'"},
//            {"'32'", "'Bob'", "'CS'"},
//            {"'64'", "'Ned'", "'EE'"},
//            {"'16'", "'Jim'", "'EE'"},
//    };
//
//    for (auto& value : values) {
//        Tuple tuple(value);
//        cout << tuple.toString(scheme) << endl;
//        relation.addTuple(tuple);
//    }
//
//    cout << "relation:" << endl;
//    cout << relation.toString();
//
//    Relation result = relation.select(2, "'CS'");
//
//    cout << "select Major='CS' result:" << endl;
//    cout << result.toString();
//
//    return 0;
//
//}