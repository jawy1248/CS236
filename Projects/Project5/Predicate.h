
#include "Parameter.h"

#include <utility>
#include <vector>
#include <string>
#include <sstream>

#pragma once

using namespace std;

class Predicate {
    private:
        string id;
        vector<Parameter> parameters;

    public:
        Predicate(string id) : id(id) {}
        Predicate() = default;

        void addValue(const string& value) { parameters.emplace_back(value); }

        vector<Parameter> getParameters() { return parameters; }

        string getName() { return id; }

        string toString() const {
            stringstream out;
            out << id + "(";
            for (unsigned i = 0; i < parameters.size(); i++) {
                out << parameters.at(i).getParameters();
                if (i < parameters.size() - 1)
                    out << ",";
            }
            out << ")";

            return out.str();
        }
};
