#include "Predicate.h"
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

class Rule {
    private:
        Predicate headPredicate;
        vector<Predicate> bodyPredicates;
    public:
        explicit Rule(Predicate headPredicate) : headPredicate(headPredicate) {}

        void addPredicate(const Predicate& p) {
            bodyPredicates.push_back(p);
        }

        string toString() {
            stringstream out;
            out << headPredicate.toString() << " :- ";
            for (unsigned i = 0; i < bodyPredicates.size(); i++) {
                out << bodyPredicates[i].toString();
                if (i < bodyPredicates.size() - 1)
                    out << ",";
            }
            out << ".";

            return out.str();
        }
};
