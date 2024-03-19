
#include "set"
#include "Scheme.h"
#include "Tuple.h"

#pragma once

using namespace std;

class Relation {
private:
    string name{};
    Scheme scheme;
    set<Tuple> tuples{};

public:
    Relation(string name, Scheme scheme) : name(std::move(name)), scheme(std::move(scheme)) {}
    Relation() = default;

    bool addTuple(const Tuple& tuple){ return tuples.insert(tuple).second; }

    unsigned size() const { return tuples.size(); }

    string toString() const {
        stringstream out;
        if (!Tuple(scheme).empty())
            for (const Tuple& tuple: tuples)
                out << "  " << tuple.toString(scheme) << endl;
        return out.str();
    }

    const string& getName() const { return name; }

    void setName(const string& tempName) { Relation::name = tempName; }

    const Scheme& getScheme() const { return scheme; }

    void setScheme(const Scheme& tempScheme) { scheme = tempScheme; }

    Relation select(unsigned ind, const string& val) const {
        Relation result(name, scheme);
        for(const Tuple& tuple : tuples)
            if(tuple.at(ind) == val)
                result.addTuple(tuple);
        return result;
    }

    Relation select(unsigned ind1, unsigned ind2) const {
        Relation result(name, scheme);
        for(const Tuple& tuple: tuples)
            if(tuple.at(ind1) == tuple.at(ind2))
                result.addTuple(tuple);
        return result;
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme, const Tuple& leftTuple, const Tuple& rightTuple){
        for(unsigned li = 0; li < leftScheme.size(); li++){
            cout << "left name: " << leftScheme.at(li) << " value: " << leftTuple.at(li) << endl;
            for(unsigned ri = 0; ri < rightScheme.size(); ri++){
                cout << "right name: " << rightScheme.at(ri) << " right: " << rightTuple.at(ri) << endl;
                if(rightScheme.at(ri) == leftScheme.at(li) && rightTuple.at(ri) != leftTuple.at(li))
                    return false;
            }
        }
        return true;
    }

    Relation join(const Relation& right) {
        for(const Tuple& leftTuple: tuples ){
            cout << "left tuple: " << leftTuple.toString(scheme) << endl;
            for(const Tuple& rightTuple: right.tuples)
                cout << "right tuple: " << rightTuple.toString(right.scheme) << endl;
        }

        return Relation();
    }

    Relation joinSchemes(){ return Relation(); }

    Relation joinTuples(){ return Relation(); }

    Relation project(const vector<unsigned>& columns) {
        Relation result(name, scheme);
        for(Tuple tuple: tuples) {
            Tuple tempTup;

            for(unsigned col: columns)
                tempTup.push_back(tuple.at(col));

            result.addTuple(tempTup);
        }
        return result;
    }

    Relation rename(vector<string> newNames) {
        Relation result(name, Scheme(newNames));
        for(const Tuple& tuple: tuples)
            result.addTuple(tuple);
        return result;
    }
};