#include <string>
#include <utility>

using namespace std;

class Parameter {
    private:
        string data{};
    public:
        Parameter(string data) : data(data) {}
        string getData() const { return data; }
};