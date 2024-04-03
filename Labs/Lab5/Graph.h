
#include <map>
#include "Node.h"

#pragma once

using namespace std;

class Graph {
private:
    map<unsigned, Node> nodes;
public:
    Graph(unsigned size){
        for(unsigned nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(unsigned start, unsigned end){ nodes[start].addEdge(end); }

    string toString() {
        stringstream out;
        for(pair<const unsigned, Node>& pair: nodes)
            out << "R" << pair.first << ":" << pair.second.toString() << '\n';
        return out.str();
    }
};