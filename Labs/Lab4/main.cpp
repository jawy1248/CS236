
#include <fstream>

#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "Interpreter.h"

using namespace std;

int main() {

    printf("Self Join\n");
    Relation studentRelation("students", Scheme( {"ID", "Name", "Major"} ));

    vector<string> studentValues[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
    };

    for (auto& value : studentValues)
        studentRelation.addTuple(Tuple(value));

    studentRelation.join(studentRelation);

    printf("\nCourse Join\n");
    Relation courseRelation("courses", Scheme( {"ID", "Course"} ));

    vector<string> courseValues[] = {
            {"'42'", "'CS 100'"},
            {"'32'", "'CS 232'"},
    };

    for (auto& value : courseValues)
        courseRelation.addTuple(Tuple(value));

    studentRelation.join(courseRelation);

}