//
// Created by Kyle Robinson on 2/14/25.
//

#pragma once
#include <map>

#include "Scheme.h"
#include "Relation.h"

class Database {
private:
    map<string, Relation> relations;

public:
    Database() {}

    void addRelation(string name, Relation rel) {
        relations.at(name) = rel;
    }

    Relation getRelation(string name) {
        return relations.at(name);
    }
    //    vector<string> names = { "ID", "Name", "Major" };
//
//    Scheme scheme(names);
//
//    Relation relation("student", scheme);
//
//    vector<string> values[] = {
//            {"'42'", "'Ann'", "'CS'"},
//            {"'32'", "'Bob'", "'CS'"},
//            {"'64'", "'Ned'", "'EE'"},
//            {"'16'", "'Jim'", "'EE'"},
//    };
//
//    for (auto& value : values) {
//        Tuple tuple(value);
//        cout << tuple.toString(scheme) << endl;
//        relation.addTuple(tuple);
//    }
//
//    cout << "relation:" << endl;
//    cout << relation.toString();
//
//    Relation result = relation.select(2, "'CS'");
//
//    cout << "select Major='CS' result:" << endl;
//    cout << result.toString();
};
