#pragma once
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Graph {

    int getIdxOfVertex(T x) {
        auto idx = find(V.begin(), V.end(), x);
        if (idx == V.end()) {
            throw "point is not in the graph";
        }
        return idx - V.begin();
    }

public:
    typedef vector<T> VType;
    typedef vector<vector<int>> GType;

    int isVertexConneted(T x, T y) {
        int vx = this->getIdxOfVertex(x);
        int vy = this->getIdxOfVertex(y);

        return this->G[vx][vy];
    }

    string title;
    VType V;
    GType G;

    void isGraphValidate() {
        int n = this->V.size();
        constexpr int strMaxLength = 1024;
        char str[strMaxLength];

        // 对角线应该全部为0
        for (int i = 0; i < n; i++) {
            if (this->G[i][i] != 0) {
                sprintf(str, "[%d,%d] should be 0", i, i);
                throw str;
            }
        }

        // G 转置前后结果相同
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (this->G[i][j] != this->G[j][i]) {
                    sprintf(str, "[%d,%d] not eq to [%d,%d]", i, j, j, i);
                    throw str;
                }
            }
        }

        if (V.size() != G.size()) {
            sprintf(str, "length of V is %d,but length of G is %d", V.size(), G.size());
            throw str;
        }

        for (VType arr : G) {
            if (arr.size() != V.size()) {
                sprintf(str, "length of V is %d,but length of item of G is %d", V.size(), arr.size());
                throw str;
            }
        }
    }
};
