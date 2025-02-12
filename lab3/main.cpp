//
// Created by Kyle Robinson on 2/12/25.
//
#include "Tuple.h"
#include "Scheme.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
    }

}