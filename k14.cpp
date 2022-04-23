#include "k14.h"
#include "c4.h"

vector<VType> k14(Graph g, VType p3) {
    if (p3.size() != 3) {
        throw "p3 should have 3 points";
    }
    vector<VType> result;

    VType endpoints = getEndPoints(g, p3);
    char midPt = 0;
    for (auto pt : p3) {
        if (endpoints[0] != pt && endpoints[1] != pt) {
            midPt = pt;
        }
    }
    if (midPt == 0) {
        throw "middle point can't be found";
    }

    for (char pt : g.V) {
        for (char pt1 : g.V) {
            // 不是中间点
            if (pt == midPt || pt1 == midPt) {
                continue;
            }

            // 不是开始点
            if (pt == endpoints[0] || pt1 == endpoints[0]) {
                continue;
            }
            // 不是结束点
            if (pt == endpoints[1] || pt1 == endpoints[1]) {
                continue;
            }

            // 和中间连有连接
            if (!g.getPoint(pt, midPt) || !g.getPoint(pt1, midPt)) {
                continue;
            }

            // 找到的两个点不连接
            if (g.getPoint(pt, pt1)) {
                continue;
            }

            // 不能是同一个点
            if (pt == pt1) {
                continue;
            }

            result.push_back({pt, pt1});
        }
    }

    return result;
}

VType k13(Graph g, VType p3) {
    if (p3.size() != 3) {
        throw "p3 should have 3 points";
    }
    VType result;

    VType endpoints = getEndPoints(g, p3);
    char midPt = 0;
    for (auto pt : p3) {
        if (endpoints[0] != pt && endpoints[1] != pt) {
            midPt = pt;
        }
    }
    if (midPt == 0) {
        throw "middle point can't be found";
    }

    for (char pt : g.V) {
        // 不是中间点
        if (pt == midPt) {
            continue;
        }

        // 不是开始点
        if (pt == endpoints[0]) {
            continue;
        }
        // 不是结束点
        if (pt == endpoints[1]) {
            continue;
        }

        // 和中间连有连接
        if (!g.getPoint(pt, midPt)) {
            continue;
        }

        result.push_back(pt);
    }

    return result;
}