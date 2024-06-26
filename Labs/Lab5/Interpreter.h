
#include <iostream>

#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

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
        doRules();
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

    void doRules(){
        cout << "Rule Evaluation" << endl;
        doRuleList(program.getRules());
    }

    void doQueries() {
        cout << "Query Evaluation" << endl;
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

    void singlePass(const vector<Rule>& rules){
        for(Rule rule: rules) {
            cout << rule.toString() << endl;
            vector<Relation> bodyRel;

            for (const Predicate& pred: rule.getBodyPreds())
                bodyRel.push_back(doPredicate(pred));

            Relation result = bodyRel.at(0);
            for(unsigned i=1; i<bodyRel.size(); i++)
                result = result.join(bodyRel.at(i));

            vector<unsigned> cols;
            for(Parameter param: rule.getHeadPred().getParameters()){
                for(unsigned i=0; i<result.getScheme().size(); i++){
                    if(param.getParameters() == result.getScheme().at(i))
                        cols.push_back(i);
                }
            }

            db.getRelationByRef(rule.getHeadPred().getName()).unionize(result.project(cols).rename(db.getRelationByRef(rule.getHeadPred().getName()).getScheme()));
        }
    }

    void doRuleList(const vector<Rule>& rules){
        unsigned preSize;
        unsigned postSize;
        unsigned count = 0;

        do {
            count++;
            preSize = db.size();
            singlePass(rules);
            postSize = db.size();
        } while(preSize != postSize);

        cout << "\nSchemes populated after " << count << " passes through the Rules.\n" << endl;
    }

    static Graph makeGraph(const vector<Rule>& rules){
        Graph graph(rules.size());

        for(unsigned start = 0; start < rules.size(); start++){
//            cout << "from rule R" << start << ": " << rules.at(start).toString() << endl;
            for(unsigned pred = 0; pred < rules.at(start).size(); pred++){
//                cout << "from body predicate: " << rules.at(start).getPred(pred).toString() << endl;
                for(unsigned end = 0; end < rules.size(); end++){
//                    cout << "to rule R" << end << ": " << rules.at(end).toString() << endl;
                    if(rules.at(start).getPred(pred).toString() == rules.at(end).getHeadPred().toString()) {
//                        cout << "dependency found: (R" << start << ",R" << end << ")" << endl;
                        graph.addEdge(start, end);
                    }
                }
            }
        }

        return graph;
    }

};