
#include <sstream>
#include <set>

#pragma once

using namespace std;

class Node {
private:
    set<unsigned> adjNodeSet;
    bool seen = false;

public:
    Node() = default;

    void addEdge(unsigned adjNode) { adjNodeSet.insert(adjNode); }

    const set<unsigned>& getAdjNodeIDs() const { return adjNodeSet; }

    void visit() { seen = true; }
    bool isVisited() {return seen; }

    string toString() const {
        stringstream out;
        for(const unsigned& nodeID: adjNodeSet)
            out << "R" << nodeID << ((&nodeID != &*(--adjNodeSet.end())) ? "," : "");
        return out.str();
    }
};