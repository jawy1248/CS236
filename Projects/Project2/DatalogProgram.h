#include <sstream>
#include <set>
#include "Predicate.h"
#include "Rule.h"

#pragma once

using namespace std;

class DatalogProgram {
    private:
        // Variables
        vector<Predicate> schemes;
        vector<Predicate> facts;
        vector<Predicate> queries;
        vector<Rule> rules;
        set<string> domain;
    public:
        // Adding to each of the variables
        void addToSchemes(Predicate& p) { schemes.push_back(p); }
        void addToFacts(Predicate& p) { facts.push_back(p); }
        void addToQueries(Predicate& p) { queries.push_back(p); }
        void addToRules(Rule& r) { rules.push_back(r); }
        void addToDomain(const string& d) { domain.insert(d); }

        // toString
        string toString(){
            stringstream out;

        }
};