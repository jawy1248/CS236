
#include <iostream>

#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {
private:
    DatalogProgram program;
    Database db;

public:
    Interpreter(DatalogProgram program) : program(program) {}

    void run() {
        doSchemes();
        doFacts();
        doQueries();
    }

    void doSchemes() {
        for (Predicate& pred : program.getSchemes()){
            Relation rel;
            vector<string> data;
            for (Parameter param : pred.getParameters())
                data.push_back(param.getParameters());
            rel.setScheme(Scheme(data));
            rel.setName(pred.getName());
            db.insert(rel);
        }
    }

    void doFacts() {
        for (Predicate pred : program.getFacts()){
            Relation& rel = db.getRelationByRef(pred.getName());
            vector<string> data;
            for (Parameter param : pred.getParameters())
                data.push_back(param.getParameters());
            rel.addTuple(Tuple(data));
        }
    }

    void doQueries() {
        for (Predicate pred : program.getQueries()){
            Relation rel = doPredicate(pred);
            cout << pred.toString() << "? ";
            if(rel.size() != 0)
                cout << "Yes(" << rel.size() << ")" << endl << rel.toString();
            else
                cout << "No" << endl;
        }
    }

    Relation doPredicate(Predicate pred) {
        Relation rel = db.getRelationCopy(pred.getName());
        vector<unsigned> cols;
        vector<string> names;

        for (unsigned row = 0; row < pred.getParameters().size(); row++){
            string param = pred.getParameters().at(row).getParameters();

            if (param.at(0) == '\'')
                rel = rel.select(row, param);
            else {
                bool checked = false;
                unsigned col = 0;
                for (; col < names.size(); col++){
                    if (names.at(col) == param){
                        checked = true;
                        break;
                    }
                }
                if (checked)
                    rel = rel.select(row, cols.at(col));
                else{
                    cols.push_back(row);
                    names.push_back(param);
                }
            }
        }

        rel = rel.project(cols);
        rel = rel.rename(names);
        return rel;
    }
};