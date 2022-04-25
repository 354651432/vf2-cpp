#ifndef VF2_STATE_H
#define VF2_STATE_H

#include "graph.h"
struct Point{
    int n, m;
    Point(int a, int b) {
        n = a;
        m  = b;
    }
};
class State {
public:
    vector<int> core_1, core_2;
    //vector<bool> in_1, out_1, in_2, out_2;
    unordered_set<int> M1, M2;
    vector<Point> M;
    unordered_set<int> T1in, T1out;
    unordered_set<int> T2in, T2out;
    unordered_set<int> fN1, fN2;
    vector<Point> ps;
    State(int sz1, int sz2);
    void removeFN(int no, int i);
};


#endif //VF2_STATE_H
