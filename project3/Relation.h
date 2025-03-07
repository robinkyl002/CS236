//
// Created by Kyle Robinson on 2/12/25.
//

#pragma once
#include "Tuple.h"
#include "Scheme.h"

#include <string>
#include <set>

using namespace std;

class Relation
{

private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation(string &name, Scheme &scheme)
        : name(name), scheme(scheme) {}

    void addTuple(Tuple &tuple)
    {
        tuples.insert(tuple);
    }

    string getName() {
        return name;
    }

    Scheme getScheme() {
        return scheme;
    }

    string toString()
    {
        stringstream out;
        // add code to print the Tuples, one per line
        for (Tuple tuple : tuples)
        {
            out << tuple.toString(scheme);
            out << endl;
        }
        return out.str();
    }

    // Example: SNAP(X,'pineapple')
    Relation selectValue(int index, string &value)
    {
        Relation result(name, scheme);
        // add tuples to the result if they meet the condition
        for (Tuple tuple : tuples)
        {
            if (value == tuple.at(index))
            {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    // Example SNAP(X,Y)
    Relation select(int index1, int index2)
    {
    }

    Relation project(vector<int> indexes)
    {

        return Relation(name, scheme);
    }

    Relation rename(vector<string> names)
    {
        for (int i = 0; i < names.size(); i++)
        {
            scheme.at(i) = names.at(i);
        }

        return Relation(name, scheme);
    };
};