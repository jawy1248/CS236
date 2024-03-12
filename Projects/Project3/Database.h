
#include "Relation.h"
#include <map>

using namespace std;

class Database {
private:
    map<string, Relation> dataMap;

public:
    string toString(){
        stringstream out;

        for (pair<string, Relation> relationEntry : dataMap)
            out << relationEntry.first << endl << relationEntry.second.toString();

        return out.str();
    }

    Relation& getRelationByRef(const string& relName){ return dataMap.at(relName); }

    Relation getRelationCopy(const string& relName){ return dataMap.at(relName); }

    void insert(const Relation& r){ dataMap.insert({r.getName(), r}); }

    unsigned size(){
        unsigned i = 0;
        for (const pair<const string, Relation> & p : dataMap)
            i += p.second.size();
        return i;
    }
};