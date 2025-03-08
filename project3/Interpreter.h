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
        vector<string> attributes;
        vector<Parameter> queryParams;

        for (Predicate datalogQuery: datalogQueries) {
            cout << datalogQuery.toString() << "?" << endl;
            name = datalogQuery.getPredicateName();
            queryParams = datalogQuery.getParameters();

            Relation result = database.getRelation(name);

            for (int i = 0; i < queryParams.size(); i++) {
//                attributes.push_back(param.toString());
                string attribute = queryParams.at(i).toString();
                if (attribute.at(0) == '\'') {
//                    database.getRelation(name).selectValue(i, attribute);
                    result = result.selectValue(i, attribute);
                } else {
                    for (int j = i + 1; j < queryParams.size(); j++) {
                        if (attribute == queryParams.at(j).toString()) {
                            result = result.select(i, j);
                        }
                    }
//                    database.getRelation(name).select(i, i+ 1);
                }
            }
            if (!result.getTuples().empty()) {

            }
//            database.getRelation(name).
        }
    }
};
