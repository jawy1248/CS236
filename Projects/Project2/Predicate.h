#include "Parameter.h"
#include <utility>
#include <vector>
#include <string>

using namespace std;

class Predicate {
    private:
        string id;
        vector<Parameter> parameters;

    public:
        explicit Predicate(string id) : id(id) {}

        void addValue(const string& value) {
            parameters.emplace_back(value);
        }

        vector<Parameter> getParameters() {
            return parameters;
        }

        string toString() {
            stringstream out;
            out << id + "(";
            for (int i = 0; i < parameters.size(); i++) {
                out << parameters[i].getData();
                if (i < parameters.size() - 1)
                    out << ",";
            }
            out << ")";

            return out.str();
        }
};
