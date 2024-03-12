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

            // Schemes
            out << "Schemes(" << schemes.size() << ((schemes.empty()) ? "):\n" : "):\n  ");
            for (unsigned i = 0; i < schemes.size(); i++) {
                out << schemes[i].toString() << "\n";
                if (i != schemes.size() - 1)
                    out << "  ";
            }

            // Facts
            out << "Facts(" << facts.size() << ((facts.empty()) ? "):\n" : "):\n  ");
            for (unsigned i = 0; i < facts.size(); i++) {
                out << facts[i].toString() << ".\n";
                if (i != facts.size() - 1)
                    out << "  ";
            }

            // Rules
            out << "Rules(" << rules.size() << ((rules.empty()) ? "):\n" : "):\n  ");
            for (unsigned i = 0; i < rules.size(); i++) {
                out << rules[i].toString() << "\n";
                if (i != rules.size() - 1)
                    out << "  ";
            }

            // Queries
            out << "Queries(" << queries.size() << ((queries.empty()) ? "):\n" : "):\n  ");
            for (unsigned i = 0; i < queries.size(); i++) {
                out << queries[i].toString() << "?\n";
                if (i != queries.size() - 1)
                    out << "  ";
            }

            // Domain
            out << "Domain(" << domain.size() << ((domain.empty()) ? "):\n" : "):\n  ");
            for (auto & d : domain) {
                out << d;
                out << ((&d != &*(--domain.end())) ? "\n  " : "\n");
            }

            // Return string
            return out.str();
        }
};