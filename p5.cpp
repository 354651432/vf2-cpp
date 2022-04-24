#include "p5.h"

// 在图g里， p 是否跟所有点pts都不连接
bool isConnect(Graph g, char p, VType pts) {
    for (auto pt : pts) {
        if (p == pt) {
            return false;
        }

        if (g.getPoint(pt, p)) {
            return true;
        }
    }

    return false;
}

bool inPoints(char pt, VType pts) {
    for (auto it : pts) {
        if (it == pt) {
            return true;
        }
    }
    return false;
}

vector<VType> P7(Graph g, VType arr) {
    vector<VType> results;

    // arr的长度肯定是5

    // 最后一个点
    auto E = arr[4];

    // 找点F
    for (auto F : g.V) {
        // 判断跟 ABCD不连接
        VType ABCD = arr;
        ABCD.pop_back();

        bool cond1 = g.getPoint(F, E);
        bool cond2 = !isConnect(g, F, ABCD);
        bool cond3 = !inPoints(F, arr);

        if (g.getPoint(F, E)
            && !isConnect(g, F, ABCD)
            && !inPoints(F, arr)) {
            // 找点G
            for (auto G : g.V) {
                if (g.getPoint(F, G) && !isConnect(g, G, arr)) {
                    results.push_back({F, G});
                }
            }
        }
    }

    return results;
}

vector<VType> Z4(Graph g, VType arr) {

    vector<VType> results;

    auto A = arr[0]; // 第一个点A
    for (auto F : g.V) {
        VType BCDE = arr;
        BCDE.erase(BCDE.begin());

        if (g.getPoint(A, F)
            && !isConnect(g, F, BCDE)
            && !inPoints(F, arr)) {

            for (auto G : g.V) {
                if (g.getPoint(A, F)
                    && !isConnect(g, F, BCDE)
                    && g.getPoint(F, G)
                    && g.getPoint(A, G)
                    && !inPoints(G, arr)) {
                    results.push_back({F, G});
                }
            }
        }
    }

    return results;
}

vector<VType> N113(Graph g, VType arr) {

    vector<VType> results;
    // 第二个点A
    auto A = arr[1];

    // 第三个点C
    auto C = arr[2];

    // 找点G
    for (auto G : g.V) {
        auto DEF = arr;

        // 剩下的DEF三个点
        DEF.erase(DEF.begin(), DEF.begin() + 2);
        if (g.getPoint(A, G)
            && g.getPoint(C, G)
            && !g.getPoint(G, arr[0])
            && !isConnect(g, G, DEF)) {

            // 找点H
            for (auto H : g.V) {
                if (g.getPoint(G, H)
                    && !isConnect(g, H, arr)) {
                    results.push_back({G, H});
                }
            }
        }
    }

    return results;
}