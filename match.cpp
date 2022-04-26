#include "match.h"
#include "v2f/state.h"

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
    return vf2(g1, g2);
}


vector<VType> vf2(Graph g1, Graph g2) {
    State s(g1, g2);

    vector<VType> ret;
    if (!s.vf2(vector<Mapping> {})) {
        return ret;
    }

    for (auto M : s.results) {
        VType result;
        for (auto ps : M) {
            result.push_back(ps.first);
        }

        ret.push_back(result);
    }

    return ret;
}
