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

//            cout << newRel.getName() << endl;
//            newRel.getScheme().printScheme();
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
//                cout << "Parameter: " << param.toString() << endl;
                values.push_back(param.toString());
            }

//            for (int i = 0; i < values.size(); i++) {
//                cout << "value at " << i << ": " << values.at(i) << endl;
//            }

            Tuple tuple = Tuple(values);
//            Scheme sch = database.getRelation(factName).getScheme();

//            sch.printScheme();
//            cout << "Tuple size: " << tuple.size() << endl;
//            cout << tuple.toString(sch) << endl;

            database.getRelation(factName).addTuple(tuple);

//            cout << database.getRelation(factName).toString() << endl;
        }
    }

    void evaluateQueries() {
        vector<Predicate> datalogQueries = dp.getQueries();
        string name;
        vector<int> variables;
        vector<Parameter> queryParams;
        vector<string> updatedScheme;

        for (Predicate datalogQuery: datalogQueries) {
            variables.clear();
            updatedScheme.clear();
            cout << datalogQuery.toString() << "? ";
            name = datalogQuery.getPredicateName();
            queryParams = datalogQuery.getParameters();

            Relation result = database.getRelation(name);
            // Select operations
            for (int i = 0; i < queryParams.size(); i++) {
                string attribute = queryParams.at(i).toString();
                if (attribute.at(0) == '\'') {
                    result = result.selectValue(i, attribute);
//                    variables.push_back(i);
                } else {
                    bool matches = false;
                    for (int j = i + 1; j < queryParams.size(); j++) {
                        if (attribute == queryParams.at(j).toString()) {
                            result = result.select(i, j);
                        }
                    }
                    for (int k = variables.size() - 1; k >= 0; k--) {
                        if(attribute == queryParams.at(variables.at(k)).toString()) {
                            matches = true;
                            break;
                        }
                    }
                    if (matches == false) {
                        variables.push_back(i);
                        updatedScheme.push_back(queryParams.at(i).toString());
                    }
                }
            }

            // Project Operations
            if (!variables.empty()) {
                result = result.project(variables);
            }

            // Rename Operations
            result = result.rename(updatedScheme);

            // Evaluation
            if (result.getTuples().empty()) {
                cout << "No" << endl;
            } else {
                cout << "Yes(" << result.getTuples().size() << ")" << endl;

                cout << result.toString() << endl;
            }

        }
    }
};
