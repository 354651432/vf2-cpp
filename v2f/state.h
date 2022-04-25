#include "../graph.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

typedef pair<char, char> Mapping;

// genPs t1 t2两个集合

class State {
    Graph g1, g2;
    vector<Mapping> M;
    vector<char>
        M1, // 结果集在G1里的结点集合
        M2, // 结果集在G2里的结点集合
        T1, // G1里与M1连接的所有点的集合
        T2; // G2里与M2连接的所有点的集合

    void genM1() {
        M1.clear();
        for (auto p : M) {
            M1.push_back(p.first);
        }
    }

    void genM2() {
        M2.clear();
        for (auto p : M) {
            M2.push_back(p.second);
        }
    }

    vector<char> genTerminal(Graph g1) {
        vector<char> ret;
        for (char pt : g1.V) {
            if (find(M1.begin(), M1.end(), pt) != M1.end()) {
                continue;
            }

            for (char pt1 : M1) {
                if (g1.G[pt][pt1]) {
                    ret.push_back(pt);
                }
            }
        }

        return ret;
    }

public:
    State(Graph g1, Graph g2)
        : g1(g1)
        , g2(g2) { }
    // 生成Ps集合
    vector<Mapping> genPs() {
        vector<Mapping> Ps;

        genM1();
        genM2();
        T1 = genTerminal(g1);
        T2 = genTerminal(g2);

        if (T1.size() > 0 && T2.size() > 0) {
            char minValue = *min_element(T2.begin(), T2.end());
            for (char pt : T1) {
                Ps.push_back(Mapping {pt, minValue});
            }
            return;
        }
        vector<char> diff1, diff2;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        char minValue = *min_element(diff2.begin(), diff2.end());

        for (char pt : diff1) {
            Ps.push_back(Mapping {pt, minValue});
        }

        return Ps;
    }

    // 状态函数
    bool F(char n, char m) {
        if (find(M1.begin(), M1.end(), n) != M1.end()
            && find(M2.begin(), M2.end(), m) != M2.end()) {
            for (Mapping p : M) {
                if (g1.G[n][p.first] != g2.G[m][p.second]) {
                    return false;
                }
            }
            return true;
        }

        auto g1TLen = T1.size();
        auto g2TLen = T2.size();

        vector<char> diff1, diff2;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        set_difference(diff1.begin(), diff1.end(), T1.begin(), T1.end(), inserter(diff1, diff1.begin()));
        set_difference(diff2.begin(), diff2.end(), T2.begin(), T2.end(), inserter(diff2, diff2.begin()));

        return g1TLen >= g2TLen && diff1.size() >= diff2.size();
    }
};