#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Scheme : public vector<string> {
private:
    vector<string> names;

public:

    Scheme(vector<string> names) : names(names) { }

    void printScheme() {
        for (auto& name: names) {
            cout << name << endl;
        }
    }

};
