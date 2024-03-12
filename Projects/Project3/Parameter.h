#include <string>
#include <utility>

#pragma once

using namespace std;

class Parameter {
    private:
        string data{};
    public:
        Parameter(string data) : data(data) {}
        string getData() const { return data; }
};