//
// Created by Kyle Robinson on 4/11/25.
//

#pragma once
#include <map>
#include <sstream>
#include <string>
#include <stack>
#include <set>

#include "Node.h"

using namespace std;

class Graph {

private:

    map<int,Node> nodes;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    Node getNode(int nodeID) {
        return nodes.at(nodeID);
    }

    stack<int> getPostOrderStack() {
        set<int> visited;
        stack<int> postorderStack;

        for (auto& pair : nodes) {
            int nodeID = pair.first;
            if (visited.find(nodeID) == visited.end()) {
                dfs(nodeID, visited, postorderStack);
            }
        }

        return postorderStack;
    }

    void dfs(int nodeID, set<int>& visited, stack<int>& postorderStack) {
        visited.insert(nodeID);
        for (int neighbor : nodes[nodeID].getAdjacentNodeIDs()) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, visited, postorderStack);
            }
        }
        postorderStack.push(nodeID);
    }

    void dfsCollectSCCs(int nodeID, set<int>& visited, set<int>& scc) {
        visited.insert(nodeID);
        scc.insert(nodeID);

        for (int neighbor : nodes[nodeID].getAdjacentNodeIDs()) {
            if (visited.find(neighbor) == visited.end()) {
                dfsCollectSCCs(neighbor, visited, scc);
            }
        }
    }

    bool loopsToSelf(int nodeID) {
        set<int> edges = nodes.at(nodeID).getAdjacentNodeIDs();
        bool loops = (edges.find(nodeID) != edges.end());

        return loops;
    }

    string toString() {
        stringstream out;

        for (auto& pair : nodes) {
            int nodeID = pair.first;
            Node node = pair.second;

            out << "R" << nodeID << ":" << node.toString() << endl;
        }

        return out.str();
    }

};
