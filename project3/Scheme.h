#pragma once
#include "Tuple.h"

#include <vector>
#include <string>

using namespace std;

class Scheme : public vector<string> {
private:
    vector<string> names;

public:

    Scheme(vector<string> names) : names(names) { }

};
