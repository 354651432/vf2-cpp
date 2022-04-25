#include "vf2.h"
#include <iostream>
void getCandidatePairs(const GraphVec &g1, const GraphVec &g2, State &s) {
    const unordered_set<int> &T1out = s.T1out;
    const unordered_set<int> &T2out = s.T2out;
    const unordered_set<int> &T1in = s.T1in;
    const unordered_set<int> &T2in = s.T2in;
    vector<Point> &p = s.ps;
    if(!T1out.empty() && !T2out.empty()) {
        int m = *max_element(T2out.begin(), T2out.end());
        for (auto n : T1out) {

            p.push_back(Point(n, m));
        }
    } else if(!T1in.empty() && !T2in.empty()) {
        int m = *max_element(T2in.begin(), T2in.end());
        for (auto n : T1in) {
            p.push_back(Point(n, m));
        }
    } else {
        int sz2 = g2.getSize(), sz1 = g1.getSize();
        int m;
        for (int i = sz2 - 1; i >= 0; --i) {
            if (s.core_2[i] == -1) {
                m = i;
                break;
            }
        }
        for (int i = 0; i < sz1; ++i) {
            if (s.core_1[i] == -1) {
                assert(i < g1.getSize() && m < g2.getSize());
                p.push_back(Point(i, m));
            }
        }
    }
}

void outputResult(const State &s) {
    for(auto p : s.M) {
        printf("%d %d\n", p.n, p.m);
    }
    printf("\n\n");
}

bool getFsem(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    if (g1.getNodeLabel(n) != g2.getNodeLabel(m)) return false;
    int np, mp, w1, w2;
    //(n, n') == (m, m')
    for (int i = g1.getHead(n); i != -1; i = g1.edge[i].next) {
        np = g1.edge[i].v; //n' in paper
        w1 = g1.edge[i].w;
        mp = s.core_1[np];
        if (mp != -1) {
            for (int j = g2.getHead(m); j != -1; j = g2.edge[j].next) {
                if (g2.edge[j].v != mp) continue;
                w2 = g2.edge[j].w;
                if (w1 != w2) return false;
                break;
            }
        }
    }

    //(n', n) == (m', m)
    for (int i = g1.getRhead(n); i != -1; i  = g1.redge[i].next) {
        np = g1.redge[i].v; //n' in paper
        w1 = g1.redge[i].w;
        mp = s.core_1[np];
        if (mp != -1) {
            for (int j = g2.getRhead(m); j != -1; j = g2.redge[j].next) {
                if (g2.redge[j].v != mp) continue;
                w2 = g2.redge[j].w;
                if (w1 != w2) return false;
                break;
            }
        }
    }
    return true;
}

bool calRpred(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    unordered_set<int> interSt;
    set_intersection(g1.pred[n].begin(), g1.pred[n].end(), s.M1.begin(), s.M1.end(), inserter(interSt, interSt.begin()));
    int mp;
    for (auto np : interSt) {
        mp = s.core_1[np];
        if (g2.pred[m].find(mp) == g2.pred[m].end()) {
            return false;
        }
    }

    interSt.clear();
    set_intersection(g2.pred[m].begin(), g2.pred[m].end(), s.M2.begin(), s.M2.end(), inserter(interSt, interSt.begin()));
    int np;
    for (auto mp : interSt) {
        np = s.core_2[mp];
        if (g1.pred[n].find(np) == g1.pred[m].end()) {
            return false;
        }
    }
    return true;
}

bool calRsucc(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    unordered_set<int> interSt;
    set_intersection(g1.succ[n].begin(), g1.succ[n].end(), s.M1.begin(), s.M1.end(), inserter(interSt, interSt.begin()));
    int mp;
    for (auto np : interSt) {
        mp = s.core_1[np];
        if (g2.succ[m].find(mp) == g2.succ[m].end()) {
            return false;
        }
    }

    interSt.clear();
    set_intersection(g2.succ[m].begin(), g2.succ[m].end(), s.M2.begin(), s.M2.end(), inserter(interSt, interSt.begin()));
    int np;
    for (auto mp : interSt) {
        np = s.core_2[mp];
        if (g1.succ[n].find(np) == g1.succ[m].end()) {
            return false;
        }
    }
    return true;
}

bool calRin(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    unordered_set<int> interSt1, interSt2;
    set_intersection(g1.succ[n].begin(), g1.succ[n].end(), s.T1in.begin(), s.T1in.end(), inserter(interSt1, interSt1.begin()));
    set_intersection(g2.succ[m].begin(), g2.succ[m].end(), s.T2in.begin(), s.T2in.end(), inserter(interSt2, interSt2.begin()));
    if (interSt1.size() < interSt2.size()) return false;
    interSt1.clear();
    interSt2.clear();

    set_intersection(g1.pred[n].begin(), g1.pred[n].end(), s.T1in.begin(), s.T1in.end(), inserter(interSt1, interSt1.begin()));
    set_intersection(g2.pred[m].begin(), g2.pred[m].end(), s.T2in.begin(), s.T2in.end(), inserter(interSt2, interSt2.begin()));
    return interSt1.size() >= interSt2.size();
}

bool calRout(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    unordered_set<int> interSt1, interSt2;
    set_intersection(g1.succ[n].begin(), g1.succ[n].end(), s.T1out.begin(), s.T1out.end(), inserter(interSt1, interSt1.begin()));
    set_intersection(g2.succ[m].begin(), g2.succ[m].end(), s.T2out.begin(), s.T2out.end(), inserter(interSt2, interSt2.begin()));
    if (interSt1.size() < interSt2.size()) return false;

    interSt1.clear();
    interSt2.clear();

    set_intersection(g1.pred[n].begin(), g1.pred[n].end(), s.T1out.begin(), s.T1out.end(), inserter(interSt1, interSt1.begin()));
    set_intersection(g2.pred[m].begin(), g2.pred[m].end(), s.T2out.begin(), s.T2out.end(), inserter(interSt2, interSt2.begin()));
    return interSt1.size() >= interSt2.size();
}

bool calRnew(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    //return true;
    unordered_set<int> interSt1, interSt2;
    set_intersection(s.fN1.begin(), s.fN1.end(), g1.pred[n].begin(), g1.pred[n].end(), inserter(interSt1, interSt1.begin()));
    set_intersection(s.fN2.begin(), s.fN2.end(), g2.pred[m].begin(), g2.pred[m].end(), inserter(interSt2, interSt2.begin()));
    if (interSt1.size() < interSt2.size()) return false;
    interSt1.clear();
    interSt2.clear();

    set_intersection(s.fN1.begin(), s.fN1.end(), g1.succ[n].begin(), g1.succ[n].end(), inserter(interSt1, interSt1.begin()));
    set_intersection(s.fN2.begin(), s.fN2.end(), g2.succ[m].begin(), g2.succ[m].end(), inserter(interSt2, interSt2.begin()));

    return interSt1.size() >= interSt2.size();
}

bool getFsyn(const GraphVec &g1, const GraphVec &g2, const State &s, int n, int m) {
    return calRpred(g1, g2, s, n, m) &&
           calRsucc(g1, g2, s, n, m);// &&
//           calRin(g1, g2, s, n, m) &&
//           calRout(g1, g2, s, n, m) &&
//           calRnew(g1, g2, s, n, m);
}


void updateTin(const GraphVec &g, unordered_set<int> &Tin, unordered_set<int> &FN, int u, const vector<int> &core) {
    int v;

    if (Tin.find(u) != Tin.end()) {
        Tin.erase(u);
    }

    for (int i = g.getRhead(u); i != -1; i = g.redge[i].next) {
        v = g.redge[i].v;
        assert(v < g.getSize());
        if (core[v] == -1) { //if v not in s
            Tin.insert(v);
        }
        if (FN.find(v) != FN.end()) {
            FN.erase(v);
        }
        //in.push_back(v);
    }
}
void updateTout(const GraphVec &g, unordered_set<int> &Tout, unordered_set<int> &FN, int u, const vector<int> &core) {
    int v;

    if (Tout.find(u) != Tout.end()) {
        Tout.erase(u);
    }

    for (int i = g.getHead(u); i != -1; i = g.edge[i].next) {
        v = g.edge[i].v;
        assert(v < g.getSize());
        if (core[v] == -1) { //if v not in s
            Tout.insert(v);
        }
        if (FN.find(v) != FN.end()) {
            FN.erase(v);
        }
        //out.push_back(v);
    }
}
State updateState(const GraphVec &g1, const GraphVec &g2, State s, int n, int m) {
    s.M1.insert(n);
    s.M2.insert(m);
    s.M.push_back(Point(n, m));
    s.core_1[n] = m;
    s.core_2[m] = n;
//    s.in_1[n] = true;
//    s.in_2[m] = true;
//    s.out_1[n] = true;
//    s.out_2[m] = true;
    s.removeFN(1, n);
    s.removeFN(2, m);
    updateTin(g1, s.T1in, s.fN1, n, s.core_1);
    updateTin(g2, s.T2in, s.fN2, m, s.core_2);
    updateTout(g1, s.T1out, s.fN1, n, s.core_1);
    updateTout(g2, s.T2out, s.fN2, m, s.core_2);
    s.ps.clear();
    return s;
}

bool match(const GraphVec &g1, const GraphVec &g2, State &s) {
    if (s.M2.size() == g2.getSize()) {
        //outputResult(s);
        return true;
    }
    //output the result
//    if (s.M.size() != 0) {
//        outputResult(s);
//    }
    getCandidatePairs(g1, g2, s);
    int n, m;
    State news(g1.getSize(), g2.getSize());
    for (auto p: s.ps) {
        n = p.n;
        m = p.m;
        assert(n < g1.getSize() && m < g2.getSize());

        if (getFsem(g1, g2, s, n, m) && getFsyn(g1, g2, s, n, m)) {
            news = updateState(g1, g2, s, n, m);
            if (match(g1, g2, news)) {
                return true;
            }
        }
    }
    return false;
}


