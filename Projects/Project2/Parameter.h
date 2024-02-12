#include <string>
#include <utility>

using namespace std;

class Parameter {
    private:
        string data{};
    public:
        explicit Parameter(string data) : data(data) {}
        string getData() { return data; }
};