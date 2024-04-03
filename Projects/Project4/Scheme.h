
#include <string>
#include <vector>
#include "algorithm"

#pragma once

using namespace std;

class Scheme : public vector<string> {
public:
    Scheme(vector<string> names) : vector<string>(names) {}
    Scheme() = default;

    static unsigned index(vector<string> names, const string& value){
        auto it = std::find(names.begin(), names.end(), value);
        if (it == names.end()) throw invalid_argument("Value DNE, Line, " + to_string(__LINE__));
        return distance(names.begin(), it);
    }
};