#pragma once
#include "Tuple.h"

#include <vector>
#include <string>

using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }

};