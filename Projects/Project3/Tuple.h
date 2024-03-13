
#include <sstream>

#include "Scheme.h"
#include "string"
#include "vector"

#pragma once

using namespace std;

class Tuple : public vector<string>{
public:
    Tuple() = default;
    Tuple(vector<string> values) : vector<string>(std::move(values)) {}

    string toString(const Scheme& scheme) const {
        stringstream out;
        for(unsigned i = 0; i < size(); i++){
            if(i > 0)
                out << ", ";
            out << scheme.at(i) << "=" << at(i);
        }
        return out.str();
    }
};