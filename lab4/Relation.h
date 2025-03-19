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

    set<Tuple> getTuples() {
        return tuples;
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
    // returns relation
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
//        cout << "selectValue at index " << index << " using value " << value << endl;
        return result;
    }

    // Example - SNAP(X,X)
    // Returns relation
    Relation select(int index1, int index2)
    {
        Relation result = Relation(name, scheme);

        for (Tuple tup : tuples) {
            if (tup.at(index1) == tup.at(index2)) {
                result.addTuple(tup);
            }
        }
        return result;
    }

    Relation project(vector<int> indexes)
    {
        vector<string> newScheme;

        for (int i = 0; i < indexes.size(); i++) {
            newScheme.push_back(scheme.at(indexes.at(i)));
        }

        Scheme updated = Scheme(newScheme);

        Relation result = Relation(name, updated);

        for (Tuple tup : tuples) {
            vector<string> newTuple;
            for (int i = 0; i < indexes.size(); i++) {
                newTuple.push_back(tup.at(indexes.at(i)));
            }
            Tuple updated = Tuple(newTuple);
            result.addTuple(updated);
        }

        return result;
    }

    Relation rename(vector<string> names)
    {
        Scheme newScheme = Scheme(names);
        Relation result = Relation(name, newScheme);

        for (Tuple tup : tuples) {
            result.addTuple(tup);
        }

        return result;
    };

    // Join function
    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
                         const Tuple& leftTuple, const Tuple& rightTuple) {
        // add code to test whether the tuples are joinable
        bool isJoinable = false;

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);
//            cout << "left name: " << leftName << " value: " << leftValue << endl;

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);
//                cout << "right name: " << rightName << " value: " << rightValue << endl;

                if (leftName == rightName) {
                    if (leftValue != rightValue) {
//                        isJoinable = true;
                        return false;
                    }
                }
            }
        }

//        return isJoinable;
        return true;
    }

    Relation join(Relation& right) {
        Relation& left = *this;
//        Relation result;
        // add code to complete the join operation

        for (Tuple leftTuple : tuples) {
            cout << "left tuple: " << leftTuple.toString(scheme) << endl;

            for (Tuple rightTuple : right.tuples) {
                Scheme rightScheme = right.getScheme();

                cout << "right tuple: " << rightTuple.toString(rightScheme) << endl;
            }
        }

        return Relation(name, scheme);
    }
};