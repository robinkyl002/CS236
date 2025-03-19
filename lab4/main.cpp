//
// Created by Kyle Robinson on 3/10/25.
//
#include "Tuple.h"
#include "Scheme.h"
#include "Relation.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

//    Scheme scheme1( { "A", "B" } );
//    Scheme scheme2( { "B", "C" } );
//
//    Tuple tuple1( {"'1'", "'2'"} );
//    Tuple tuple2( {"'3'", "'4'"} );
////
////    cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl;
//
//    Scheme scheme3( { "X", "Y" } );
//    Scheme scheme4( { "X", "Y", "Z" } );
//
//    Tuple tuple3( {"'1'", "'4'"} );
//    Tuple tuple4( {"'1'", "'2'", "'4'"} );
//
//    // false
//    cout << Relation::joinable(scheme1, scheme2, tuple1, tuple2) << endl;
//    // true
//    cout << Relation::joinable(scheme2, scheme3, tuple1, tuple2) << endl;
//    // true
//    cout << Relation::joinable(scheme3, scheme4, tuple1, tuple4) << endl;
//    // false
//    cout << Relation::joinable(scheme3, scheme4, tuple3, tuple4) << endl;

string name = "students";
Scheme scheme = Scheme({"ID", "Name", "Major"});

    Relation studentRelation(name, scheme);

    vector<string> studentValues[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
    };

    for (auto& value : studentValues){
        Tuple newTuple = Tuple(value);
        studentRelation.addTuple(newTuple);
    }

    string secondName = "courses";
    Scheme courseScheme = Scheme( {"ID", "Course"} );

    Relation courseRelation(secondName, courseScheme);

    vector<string> courseValues[] = {
            {"'42'", "'CS 100'"},
            {"'32'", "'CS 232'"},
    };

    for (auto& value : courseValues) {
        Tuple newTuple = Tuple(value);
        courseRelation.addTuple(newTuple);
    }

//    cout << courseRelation.toString() << endl;

//    studentRelation.join(studentRelation);

    studentRelation.join(courseRelation);

    return 0;

}