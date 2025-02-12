#pragma once
#include "Tuple.h"

#include <vector>
#include <string>

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }

};