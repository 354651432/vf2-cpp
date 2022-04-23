#include "c4.h"

VType diffAPoint(VType points, char pt) {
    VType result;
    for (auto it : points) {
        if (pt != it) {
            result.push_back(it);
        }
    }

    if (result.size() != 2) {
        throw "there should have 2 points";
    }
    return result;
}

// 找到顶点
VType getEndPoints(Graph g, VType points) {
    if (points.size() != 3) {
        throw "p3 should have 3 points";
    }

    for (char pt : points) {
        VType remainPoints = diffAPoint(points, pt);
        if (g.getPoint(pt, remainPoints[0]) && g.getPoint(pt, remainPoints[1])) {
            return remainPoints;
        }
    }

    throw "no end points found";
}

VType C4(Graph g, VType points) {
    VType result;
    VType endpoints = getEndPoints(g, points);
    for (char i : g.V) {
        if (find(points.begin(), points.end(), i) != points.end()) {
            continue;
        }

        if (g.getPoint(i, endpoints[0]) == 1 && g.getPoint(i, endpoints[1]) == 1) {
            result.push_back(i);
        }
    }
    return result;
}