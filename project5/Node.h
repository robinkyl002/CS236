//
// Created by Kyle Robinson on 4/11/25.
//

#pragma once
#include <string>
#include <sstream>
#include <set>

using namespace std;

class Node {

private:

    set<int> adjacentNodeIDs;

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    set<int> getAdjacentNodeIDs () {
        return adjacentNodeIDs;
    }

    string toString() {
        stringstream out;

        for (auto it = adjacentNodeIDs.begin(); it != adjacentNodeIDs.end(); it++) {
            out << "R" << *it;

            if (next(it) != adjacentNodeIDs.end()) {
               out << ",";
            }
        }

        return out.str();
    }

};
