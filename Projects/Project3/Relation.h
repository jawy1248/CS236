
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