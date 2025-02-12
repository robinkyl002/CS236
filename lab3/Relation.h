//
// Created by Kyle Robinson on 2/12/25.
//

#pragma once
#include "Tuple.h"
#include "Scheme.h"

#include <string>
#include <set>

using namespace std;

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string& name, const Scheme& scheme)
            : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

};