#include "match.h"
#include "demo.h"

bool graphEq(Graph g1, Graph g2) {
    int n = g1.V.size();
    if (n != g2.V.size()) {
        return false;
    }
    for (size_t i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g1.G[i][j] != g2.G[i][j]) {
                return false;
            }
        }
    }

    return true;
}

vector<VType> match(Graph g1, Graph g2) {
    int n = g2.V.size();

    Combination cb(g1.V);
    auto points = cb.run(n);

    vector<VType> result;
    for (VType arr : points) {
        Graph subGrap = g1.subGraph(arr);
        if (graphEq(subGrap, g2)) {
            result.push_back(arr);
        }
    }

    return result;
}
