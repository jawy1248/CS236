
#include <sstream>
#include <set>

#pragma once

using namespace std;

class Node {
private:
    set<unsigned> adjNodeSet;
    bool seen = false;
    unsigned poNum = 0;
public:
    void addEdge(unsigned adjNode) { adjNodeSet.insert(adjNode); }
    void visit() { seen = true; }
    void addPoNum(unsigned newPoNum) {
        poNum = newPoNum;
        if(!seen) throw logic_error("Node not visited");
    }

    string toString() const {
        stringstream out;
        for(const unsigned& nodeID: adjNodeSet)
            out << "R" << nodeID << ((&nodeID != &*(--adjNodeSet.end())) ? "," : "");
        return out.str();
    }
};