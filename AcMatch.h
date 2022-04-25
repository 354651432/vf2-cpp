#pragma once
#include "combination.h"
#include "graph.h"
#include "match.h"

class AcMatch : public Combination<char> {
    Graph g1, g2;

protected:
    bool useResult(vector<char> arr) {
        if (arr.size() < g2.V.size()) {
            return true;
        }

        vector<VType> result;
        Graph subGrap = g1.subGraph(arr);
        if (graphEq(subGrap, g2)) {
            result.push_back(arr);
            return true;
        }

        return false;
    }

public:
    AcMatch(Graph g1, Graph g2)
        : g1(g1)
        , g2(g2)
        , Combination(g1.V) {
    }

    vector<vector<char>> match() {
        return this->arrangement((int)g2.V.size());
    }
};