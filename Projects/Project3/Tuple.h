
#include <sstream>

#include "Scheme.h"
#include "string"
#include "vector"

#pragma once

using namespace std;

class Tuple : public vector<string>{
private:
    vector<string> values;
public:
    Tuple(vector<string> values) : vector<string>(values) {}

    string toString(const Scheme& scheme) const {
        stringstream out;
        for(unsigned i = 0; i < size(); i++){
            if(i > 0)
                out << ", ";
            const string& name = scheme.at(i);
            const string& val = at(i);
            out << name << "=" << val;
        }
        return out.str();
    }
};