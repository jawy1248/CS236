
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
            for (const Parameter& param : pred.getParameters())
                data.push_back(param.getParameters());
            rel.addTuple(Tuple(data));
        }
    }

    void doRules(){
        bool back = true;
        vector<Rule> rules = program.getRules();
        Graph graph = makeGraph(rules);

        cout << graph.toString() << endl << "Rule Evaluation" << endl;

        for(const set<unsigned>& SCC: graph.DFS_ForRest_SCC(makeGraph(rules, back).DFS_ForRest())) {
            vector<Rule> tempRule{};
            stringstream out;

            for(const unsigned& scc : SCC) {
                tempRule.push_back(rules.at(scc));
                out << 'R' << scc << ((&scc != &*(--SCC.end())) ? ',' : '\n');
            }

            if (!out.str().empty()) {
                cout << "SCC: " << out.str() << doRuleList(tempRule) << out.str() << endl;
            }

        }
    }

    void doQueries() {
        cout << "\nQuery Evaluation" << endl;
        for (const Predicate& pred : program.getQueries()){
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

    string doRuleList(const vector<Rule>& rules){
        unsigned preSize;
        unsigned postSize;
        unsigned count = 0;

        do {
            count++;
            preSize = db.size();
            singlePass(rules);
            postSize = db.size();
        } while(preSize != postSize && ((rules.size() != 1) || isSelfDep(rules)));

        return to_string(count) + " passes: ";
    }

    static bool isSelfDep(const vector<Rule>& rules){
        vector<Predicate> loop = rules.at(0).getBodyPreds();
        return any_of(loop.begin(), loop.end(), [rules](const Predicate& pred) { return (pred.getName() == rules.at(0).getHeadPred().getName()); });
    }

    static Graph makeGraph(const vector<Rule>& rules, bool back = false){
        Graph graph(rules.size());

        for(unsigned start = 0; start < rules.size(); start++){
            for(unsigned pred = 0; pred < rules.at(start).getBodyPreds().size(); pred++){
                for(unsigned end = 0; end < rules.size(); end++){
                    if(rules.at(end).getHeadPred().getName() == rules.at(start).getBodyPreds().at(pred).getName()) {
                        graph.addEdge((back) ? end : start, (back) ? start : end);
                    }
                }
            }
        }

        return graph;
    }

};