
#include <map>
#include <stack>
#include "Node.h"

#pragma once

using namespace std;

class Graph {
private:
    map<unsigned, Node> nodes;
    stack<unsigned> currStack{};

public:
    Graph(unsigned size){
        for(unsigned nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(unsigned start, unsigned end){ nodes.at(start).addEdge(end); }

    void DFS(unsigned start) {
        if(nodes.at(start).isVisited())
            return;

        nodes.at(start).visit();
        for(const unsigned& child: nodes.at(start).getAdjNodeIDs()){
            if(!nodes.at(child).isVisited())
                DFS(child);
        }

        currStack.push(start);
    }

    stack<unsigned> DFS_ForRest() {
        for(unsigned start = 0; start < nodes.size(); start++){
            if(!nodes.at(start).isVisited())
                DFS(start);
        }

        return currStack;
    }

    set<unsigned> DFS_SCC(unsigned start) {
        if(nodes.at(start).isVisited())
            return {};

        set<unsigned> res;

        nodes.at(start).visit();
        res.insert(start);
        for(const unsigned& child: nodes.at(start).getAdjNodeIDs()){
            if(!nodes.at(child).isVisited()) {
                set<unsigned> temp = DFS_SCC(child);
                res.insert(temp.begin(), temp.end());
            }
        }

        currStack.push(start);
        return res;
    }

    vector<set<unsigned>> DFS_ForRest_SCC(stack<unsigned> prev) {
        set<unsigned> res;
        vector<set<unsigned>> SCC;
        while(!prev.empty()) {
            unsigned top = prev.top();
            if(!nodes.at(top).isVisited()) {
                set<unsigned> temp = DFS_SCC(top);
                res.insert(temp.begin(), temp.end());
            } else {
                SCC.push_back(res);
                res.clear();
                prev.pop();
            }
        }
        return SCC;
    }

    string toString() {
        stringstream out;
        out << "Dependency Graph\n";
        for(const pair<const unsigned, Node>& pair: nodes)
            out << "R" << pair.first << ":" << pair.second.toString() << '\n';
        return out.str();
    }
};