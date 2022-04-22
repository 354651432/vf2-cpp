#include "demo.h"

namespace Demo1 {
    Graph getBigGraph() {
        Graph g;
        g.V = {'1', '2', '3', '4', '5', '6', '7'};
        g.G = {
            {0, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 1},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0}};

        return g;
    }

    VType getP3() {
        return VType {'1', '2', '3'};
    }

    VType test245() {
        Graph g = getBigGraph();
        return g.getP3Match({'2', '4', '5'});
    }

    VType test236() {
        Graph g = getBigGraph();
        return g.getP3Match({'2', '3', '6'});
    }

    void resultDisplay(string msg, VType result) {
        cout << msg << endl;
        if (result.size() <= 0) {
            cout << "no result" << endl;
            return;
        }

        cout << "results:" << endl;
        for (auto i : result) {
            cout << i << endl;
        }
    }
}