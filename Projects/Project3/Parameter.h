#include <string>
#include <utility>

#pragma once

using namespace std;

class Parameter {
    private:
        string data{};
    public:
        Parameter(string data) : data(std::move(data)) {}
        string getParameters() const { return data; }
};