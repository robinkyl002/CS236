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
        cout << "Rule Evaluation" << endl;

        int passes = 0;
        bool changes = true;

        vector<Rule> rules = dp.getRules();
        while (changes) {
            passes++;
            int size = 0;
            changes = false;
            for (Rule dpRule : rules) {
                cout << dpRule.toString() << "." << endl;
                string name;

                vector<Relation> bodyRels;
                vector<Predicate> intermediateRules = dpRule.getPredicateList();

                for (Predicate intRule : intermediateRules) {
                    Relation r = evalPredicates(intRule);
                    bodyRels.push_back(r);
                }

                Relation joinedRelation = bodyRels.at(0);
                for (int i = 0; i < bodyRels.size(); i++) {
                    joinedRelation = joinedRelation.join(bodyRels.at(i));
                }

                Predicate head = dpRule.getHeadPredicate();

                vector<int> indexes;
                Scheme updatedScheme = joinedRelation.getScheme();
                vector<Parameter> headParams = head.getParameters();

                for (int i = 0; i < headParams.size(); i++) {
                    string name = headParams.at(i).toString();
                    for (int k = 0; k < updatedScheme.size(); k++) {
                        if (updatedScheme.at(k) == name) {
                            indexes.push_back(k);
                            break;
                        }
                    }
                }

                Relation projectedRelation = joinedRelation.project(indexes);
                vector<string> newNames;

                for (int j = 0; j < headParams.size(); j++) {
                    newNames.push_back(headParams.at(j).toString());
                }

                projectedRelation = projectedRelation.rename(newNames);

                string headName = head.getPredicateName();
                Relation& target = database.getRelation(headName);

                bool added = target.unionFunction(projectedRelation);

                if(added) {
                    changes = true;
                }
            }
        }

        cout << endl;
        cout << "Schemes populated after " << passes << " passes through the Rules.\n" << endl;
    }

    static Graph makeGraph(const vector<Rule>& rules) {

        Graph graph(rules.size());
        // add code to add edges to the graph for the rule dependencies
        int fromIndex = 0;
        int toIndex = 0;
        for (Rule rule : rules) {
//            cout << "from rule R" << fromIndex << ": " << rule.toString() << endl;

            for (Predicate& pred : rule.getPredicateList()) {
//                cout << "from body predicate: " << pred.toString() << endl;
                toIndex = 0;
                for (Rule toRule : rules) {
//                    cout << "to rule R" << toIndex << ": " << toRule.toString() << endl;

                    if (pred.getPredicateName() == toRule.getHeadPredicate().getPredicateName()) {
                        graph.addEdge(fromIndex, toIndex);

//                        cout << "dependency found: (R" << fromIndex << ",R" << toIndex << ")" << endl;
                    }

                    toIndex++;
                }
            }

            fromIndex++;

        }
        return graph;

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
