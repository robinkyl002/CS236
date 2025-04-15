//
// Created by Kyle Robinson on 2/14/25.
//

#pragma once
#include "Database.h"
#include "DatalogProgram.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Interpreter {
private:
    DatalogProgram dp;
    Database database;

public:
    Interpreter(DatalogProgram dp) : dp(dp) {}

    void print() {
        cout << dp.toString() << endl;
    }

    void interpret() {
        evaluateSchemes();
        evaluateFacts();
        evaluateRules();
        evaluateQueries();
    }

    void evaluateSchemes() {
        vector<Predicate> datalogSchemes = dp.getSchemes();
        for (Predicate datalogScheme: datalogSchemes) {
            vector<string> attributes;
            string schemeName = datalogScheme.getPredicateName();
            vector<Parameter> schemeParams = datalogScheme.getParameters();

            for (Parameter param: schemeParams) {
                attributes.push_back(param.toString());
            }
            Scheme newScheme = Scheme(attributes);
            Relation newRel = Relation(schemeName, newScheme);

            database.addRelation(schemeName, newRel);
        }
    }

    void evaluateFacts() {
        vector<Predicate> datalogFacts = dp.getFacts();

        for (Predicate datalogFact : datalogFacts) {
            vector<string> values;
            string factName = datalogFact.getPredicateName();
            vector<Parameter> factParams = datalogFact.getParameters();

            for (Parameter param : factParams) {
                values.push_back(param.toString());
            }

            Tuple tuple = Tuple(values);

            database.getRelation(factName).addTuple(tuple);
        }
    }

    void evaluateRules() {
        cout << "Dependency Graph" << endl;

        vector<Rule> rules = dp.getRules();

        Graph dependencyGraph = makeGraph(rules);

        Graph reverseGraph = makeReverseGraph(rules);

        cout << dependencyGraph.toString() << endl;

//        cout << reverseGraph.toString() << endl;
        vector<set<int>> sccs = findSCCs(dependencyGraph, reverseGraph);

        cout << "Rule Evaluation" << endl;
        for (set<int>& scc : sccs) {
            int passes = 0;
            bool changes = false;

            cout << "SCC: ";
            bool first = true;
            for (int id : scc) {
                if (!first) cout << ",";
                cout << "R" << id;

                first = false;
            }
            cout << endl;

            do {
                changes = false;
                passes++;

                for (int ruleIndex : scc) {
                    Rule& rule = rules[ruleIndex];
                    cout << rule.toString() << "." << endl;

                    vector<Relation> bodyRelations;
                    for (const Predicate& pred : rule.getPredicateList()) {
                        bodyRelations.push_back(evalPredicates(pred));
                    }

                    Relation combined = bodyRelations.at(0);
                    for (int i = 1; i < bodyRelations.size(); ++i) {
                        combined = combined.join(bodyRelations[i]);
                    }

                    Predicate head = rule.getHeadPredicate();
                    vector<int> indexes;
                    vector<Parameter> headParams = head.getParameters();
                    Scheme joinedScheme = combined.getScheme();

                    for (Parameter& param : headParams) {
                        for (int k = 0; k < joinedScheme.size(); ++k) {
                            if (joinedScheme.at(k) == param.toString()) {
                                indexes.push_back(k);
                                break;
                            }
                        }
                    }

                    Relation projected = combined.project(indexes);

                    vector<string> newNames;
                    for (Parameter& param : headParams) {
                        newNames.push_back(param.toString());
                    }

                    projected = projected.rename(newNames);

                    Relation& target = database.getRelation(head.getPredicateName());
                    if (target.unionFunction(projected)) {
                        changes = true;
                    }
                }
            } while((scc.size() > 1 || isSelfDependent(*scc.begin(), dependencyGraph)) && changes);

            cout << passes << " passes: ";
            first = true;
            for (int id : scc) {
                // only add comma if it is not the first component
                if (!first) cout << ",";
                cout << "R" << id;

                // make sure commas are printed after first comment is printed
                first = false;
            }
            cout << endl;
        }

        cout << endl;
    }

    vector<set<int>> findSCCs(Graph& forward, Graph& reverse) {
        stack<int> order = reverse.getPostOrderStack();

        set<int> visited;
        vector<set<int>> sccs;

        while (!order.empty()) {
            int nodeID = order.top();
            order.pop();

            if (visited.find(nodeID) == visited.end()) {
                set<int> scc;
                forward.dfsCollectSCCs(nodeID, visited, scc);
                sccs.push_back(scc);
            }
        }

        return sccs;
    }

    bool isSelfDependent(int nodeID, Graph& graph) {
        return graph.loopsToSelf(nodeID);
    }


    static Graph makeGraph(const vector<Rule>& rules) {

        Graph graph(rules.size());
        // add code to add edges to the graph for the rule dependencies
        int fromIndex = 0;
        int toIndex = 0;
        for (Rule rule : rules) {
            for (Predicate& pred : rule.getPredicateList()) {
                toIndex = 0;
                for (Rule toRule : rules) {
                    if (pred.getPredicateName() == toRule.getHeadPredicate().getPredicateName()) {
                        cout << "from: " << fromIndex << " to: " << toIndex << endl;
                        graph.addEdge(fromIndex, toIndex);
                    }
                    toIndex++;
                }
            }
            fromIndex++;
        }
        return graph;

    }

    static Graph makeReverseGraph(const vector<Rule>& rules) {
        Graph reverseGraph(rules.size());

        int fromIndex = 0;
        for (Rule rule : rules) {
            for (Predicate& pred : rule.getPredicateList()) {
                int toIndex = 0;
                for (Rule toRule : rules) {
                    if (pred.getPredicateName() == toRule.getHeadPredicate().getPredicateName()) {
                        cout << "to: " << toIndex << " from: " << fromIndex << endl;
                        // put edge with to first
                        reverseGraph.addEdge(toIndex, fromIndex);
                    }
                    toIndex++;
                }
            }
            fromIndex++;
        }
        return reverseGraph;
    }

    void evaluateQueries() {
        cout << "Query Evaluation" << endl;

        for (Predicate datalogQuery: dp.getQueries()) {
            cout << datalogQuery.toString() << "? ";

            Relation result = evalPredicates(datalogQuery);
            if (result.getTuples().empty()) {
                cout << "No" << endl;
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;

                if(!result.getScheme().empty()) {
                    Scheme relScheme = result.getScheme();
                    for (Tuple tup : result.getTuples()) {
                        cout << "  " << tup.toString(relScheme) << endl;
                    }
                }
            }

        }
    }

    Relation evalPredicates(Predicate predicate) {
        Relation relation = database.getRelation(predicate.getPredicateName());
        vector<int> variables;
        vector<string> updatedScheme;
        string name = predicate.getPredicateName();
        vector<Parameter> params = predicate.getParameters();

        Relation result = database.getRelation(name);
        // Select operations
        for (int i = 0; i < params.size(); i++) {
            string attribute = params.at(i).toString();
            if (attribute.at(0) == '\'') {
                result = result.selectValue(i, attribute);
//                    variables.push_back(i);
            } else {
                bool matches = false;
                for (int j = i + 1; j < params.size(); j++) {
                    if (attribute == params.at(j).toString()) {
                        result = result.select(i, j);
                    }
                }
                for (int k = variables.size() - 1; k >= 0; k--) {
                    if(attribute == params.at(variables.at(k)).toString()) {
                        matches = true;
                        break;
                    }
                }
                if (matches == false) {
                    variables.push_back(i);
                    updatedScheme.push_back(params.at(i).toString());
                }
            }
        }

        // Project Operations
        if (!variables.empty()) {
            result = result.project(variables);
        }

        // Rename Operations
        result = result.rename(updatedScheme);

        return result;

    }
};
