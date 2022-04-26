#include "../graph.h"
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef pair<char, char> Mapping;

// genPs t1 t2两个集合

class State {
public:
    Graph g1, g2;

    vector<char> genFirstM(vector<Mapping> M) {
        vector<char> ret;
        for (auto p : M) {
            ret.push_back(p.first);
        }
        return ret;
    }

    vector<char> genSecondM(vector<Mapping> M) {
        vector<char> ret;
        for (auto p : M) {
            ret.push_back(p.second);
        }
        return ret;
    }

    vector<char> genTerminal(Graph g, vector<char> M) {
        vector<char> ret;
        for (char pt : g.V) {
            if (find(M.begin(), M.end(), pt) != M.end()) {
                continue;
            }

            for (char pt1 : M) {
                if (g.getPoint(pt, pt1)) {
                    ret.push_back(pt);
                }
            }
        }

        return ret;
    }

    // M是否包含整个G2
    bool coversG2(vector<Mapping> M) {
        map<char, bool> core;
        for (auto pr : M) {
            core[pr.second] = true;
        }

        for (char pt : g2.V) {
            if (!core[pt]) {
                return false;
            }
        }

        return true;
    }

    State(Graph g1, Graph g2)
        : g1(g1)
        , g2(g2) {
        for (auto p1 : g1.V) {
            for (auto p2 : g2.V) {
                Ps.push_back({p1, p2});
            }
        }
    }

    vector<Mapping> Ps;
    // 生成Ps集合
    vector<Mapping> genPs(vector<Mapping> M) {
        // return this->Ps;

        vector<Mapping> Ps;

        auto M1 = genFirstM(M);
        auto M2 = genSecondM(M);

        auto T1 = genTerminal(g1, M1);
        auto T2 = genTerminal(g2, M2);

        if (T1.size() > 0 && T2.size() > 0) {
            char minValue = *min_element(T2.begin(), T2.end());
            for (char pt : T1) {
                Ps.push_back({pt, minValue});
            }
            return Ps;
        }

        vector<char> diff1, diff2;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        char minValue = *min_element(diff2.begin(), diff2.end());

        for (char pt : diff1) {
            Ps.push_back({pt, minValue});
        }

        return Ps;
    }

    // 状态函数
    bool F(vector<Mapping> M, char n, char m) {
        auto M1 = genFirstM(M);
        auto M2 = genSecondM(M);

        auto T1 = genTerminal(g1, M1);
        auto T2 = genTerminal(g2, M2);

        if (find(M1.begin(), M1.end(), n) != M1.end()
            && find(M2.begin(), M2.end(), m) != M2.end()) {
            for (Mapping p : M) {
                if (g1.getPoint(n, p.first) != g2.getPoint(m, p.second)) {
                    return false;
                }
            }
            return true;
        }

        auto g1TLen = T1.size();
        auto g2TLen = T2.size();

        vector<char> diff1, diff2, diff11, diff22;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        set_difference(diff1.begin(), diff1.end(), T1.begin(), T1.end(), inserter(diff11, diff11.begin()));
        set_difference(diff2.begin(), diff2.end(), T2.begin(), T2.end(), inserter(diff22, diff22.begin()));

        return g1TLen >= g2TLen && diff11.size() >= diff22.size();
    }
    vector<Mapping> add(vector<Mapping> M, char n, char m) {
        M.push_back({n, m});
        return M;
    }

    bool MappingsEq(vector<Mapping> Mp1, vector<Mapping> Mp2) {
        if (Mp1.size() != Mp2.size()) {
            return false;
        }

        for (size_t i = 0; i < Mp1.size(); i++) {
            if (Mp1[i].first != Mp2[i].first) {
                return false;
            }

            if (Mp1[i].second != Mp2[i].second) {
                return false;
            }
        }
        return true;
    }
    bool inResult(vector<Mapping> M) {
        for (vector<Mapping> res : results) {
            for (int i = 0; i < M.size(); i++) {
                if (MappingsEq(res, M)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isResult(vector<Mapping> M) {
        for (Mapping p1 : M) {
            for (Mapping p2 : M) {
                if (g1.getPoint(p1.first, p2.first) != g2.getPoint(p1.second, p2.second)) {
                    return false;
                }
            }
        }

        // 判断不在最终结果集里面
        return !inResult(M);
    }

    vector<vector<Mapping>> results;

    int vf2(vector<Mapping> M) {
        if (coversG2(M)) {
            if (isResult(M)) {
                results.push_back(M);
                return 1;
            }

            return 0;
        }

        vector<Mapping> ps = genPs(M);

        int ret = 0;
        for (auto pr : ps) {
            if (F(M, pr.first, pr.second)) {
                ret += vf2(add(M, pr.first, pr.second));
            }
        }
        // restore data structure
        return ret;
    }
};