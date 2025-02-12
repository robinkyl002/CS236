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

    string toString() const {
        stringstream out;
        // add code to print the Tuples, one per line
        for (Tuple tuple : tuples) {
            out << tuple.toString(scheme);
            out << endl;
        }
        return out.str();
    }


    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        // add tuples to the result if they meet the condition
        for (Tuple tuple: tuples) {
            if (value == tuple.at(index)){
                result.addTuple(tuple);
            }
        }
        return result;
    }
};