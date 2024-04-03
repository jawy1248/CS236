
#include <set>
#include <map>

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
    Relation(string name, Scheme scheme) : name(name), scheme(scheme) {}
    Relation() = default;

    bool addTuple(const Tuple& tuple){ return tuples.insert(tuple).second; }

    set<Tuple> getTuples() { return tuples; }

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

    static bool joinable(const Tuple& t1, const Tuple& t2, const map<unsigned, unsigned>& overlap) {
        return !any_of(overlap.begin(), overlap.end(), [t1, t2](const pair<unsigned, unsigned>& p){ return t1.at(p.first) != t2.at(p.second); });
    }

    static Scheme joinSchemes(Scheme s1, Scheme s2, vector<unsigned>& columns){
        Scheme out;
        for(unsigned i=0; i<s1.size(); i++)
            out.push_back(s1.at(i));
        for(unsigned col: columns)
            out.push_back(s2.at(col));
        return out;
    }

    static Tuple joinTuples(Tuple t1, Tuple t2, const vector<unsigned>& columns){
        Tuple out;
        for(unsigned i=0; i<t1.size(); i++)
            out.push_back(t1.at(i));
        for(unsigned col: columns)
            out.push_back(t2.at(col));
        return out;
    }

    Relation join(Relation r) {
        Relation out;
        vector<unsigned> columns;
        map<unsigned, unsigned> overlap;

        for(unsigned i=0; i<r.getScheme().size(); i++){
            bool unique = true;
            for(unsigned j=0; j<scheme.size(); j++){
                if(r.getScheme().at(i) == scheme.at(j)){
                    overlap.insert({j, i});
                    unique = false;
                }
            }
            if(unique) columns.push_back(i);
        }

        out.setName(name + "+" + r.getName());
        out.setScheme(joinSchemes(scheme, r.getScheme(), columns));

        for(const Tuple& t1: tuples){
            for(const Tuple& t2: r.getTuples()){
                if(joinable(t1, t2, overlap))
                    out.addTuple(joinTuples(t1, t2, columns));
            }
        }

        return out;
    }

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

    void unionize(Relation toAdd) {
        if(scheme != toAdd.getScheme())
            throw invalid_argument("Schemes are too different to combine. Line: " + to_string(__LINE__));

        for(const Tuple& tuple: toAdd.getTuples()){
            if(addTuple(tuple) && !tuple.empty())
                cout << "  " << tuple.toString(scheme) << endl;
        }
    }
};