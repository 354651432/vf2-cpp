#include "graph.hpp"
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;

// 参数T代表图的结点类型
template <typename T>
class Vf2 {
public:
    typedef pair<T, T> Mapping;
    typedef vector<Mapping> MappingSet;
    typedef vector<T> PointSet;
    typedef Graph<T> Vf2Graph;

    Vf2(const Vf2Graph& g1, const Vf2Graph& g2)
        : g1(g1)
        , g2(g2) {
    }

    // 返回值代表不重复的解的个数
    int vf2(const MappingSet& state) {
        if (isCoversG2(state)) {
            if (isResult(state)) {
                results.push_back(state);
                return 1;
            }

            return 0;
        }

        MappingSet ps = buildPs(state);

        int ret = 0;
        for (auto pr : ps) {
            ret += vf2(add(state, pr.first, pr.second));
        }
        // restore data structure
        return ret;
    }

    vector<MappingSet> getResults() {
        return results;
    }

    static vector<MappingSet> runV2f(const Vf2Graph& g1, const Vf2Graph& g2) {
        Vf2 algorObj(g1, g2);
        algorObj.vf2(MappingSet {});

        return algorObj.getResults();
    }

private:

    Vf2Graph g1, g2;

    vector<MappingSet> results;

    PointSet getFirstOfMappingSet(const MappingSet& state) {
        PointSet ret;
        for (auto p : state) {
            ret.push_back(p.first);
        }
        return ret;
    }

    PointSet getSecondOfMappingSet(const MappingSet& state) {
        PointSet ret;
        for (auto p : state) {
            ret.push_back(p.second);
        }
        return ret;
    }

    PointSet getTerminalPoint(Vf2Graph& g, const PointSet& state) {
        PointSet ret;
        for (T pt : g.V) {
            if (find(state.begin(), state.end(), pt) != state.end()) {
                continue;
            }

            for (T pt1 : state) {
                if (g.isVertexConneted(pt, pt1) > 0) {
                    ret.push_back(pt);
                }
            }
        }

        return ret;
    }

    // M是否包含整个G2
    bool isCoversG2(const MappingSet& state) {
        map<T, bool> core;
        for (auto pr : state) {
            core[pr.second] = true;
        }

        for (T pt : g2.V) {
            if (!core[pt]) {
                return false;
            }
        }

        return true;
    }

    // 生成Ps集合
    MappingSet buildPs(const MappingSet& state) {

        MappingSet ps;

        PointSet M1 = getFirstOfMappingSet(state);
        PointSet M2 = getSecondOfMappingSet(state);

        PointSet T1 = getTerminalPoint(g1, M1);
        PointSet T2 = getTerminalPoint(g2, M2);

        if (T1.size() > 0 && T2.size() > 0) {
            T minValue = *min_element(T2.begin(), T2.end());
            for (T pt : T1) {
                if (F(state, pt, minValue, M1, M2, T1, T2)) { // 这里调用F 函数过滤，防止了重复构造 M1 M2 T1 T2
                    ps.push_back({pt, minValue});
                }
            }
            return ps;
        }

        PointSet diff1, diff2;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        T minValue = *min_element(diff2.begin(), diff2.end());

        for (T pt : diff1) {
            if (F(state, pt, minValue, M1, M2, T1, T2)) {
                ps.push_back({pt, minValue});
            }
        }

        return ps;
    }

    // 状态函数
    bool F(const MappingSet& state, T n, T m,
        PointSet M1,
        PointSet M2,
        PointSet T1,
        PointSet T2) {
        auto g1TLen = T1.size();
        auto g2TLen = T2.size();

        PointSet diff1, diff2, diff11, diff22;
        set_difference(g1.V.begin(), g1.V.end(), M1.begin(), M1.end(), inserter(diff1, diff1.begin()));
        set_difference(g2.V.begin(), g2.V.end(), M2.begin(), M2.end(), inserter(diff2, diff2.begin()));

        set_difference(diff1.begin(), diff1.end(), T1.begin(), T1.end(), inserter(diff11, diff11.begin()));
        set_difference(diff2.begin(), diff2.end(), T2.begin(), T2.end(), inserter(diff22, diff22.begin()));

        return g1TLen >= g2TLen && diff11.size() >= diff22.size();
    }

    MappingSet add(MappingSet M, T n, T m) {
        M.push_back({n, m});
        return M;
    }

    bool MappingsEq(const MappingSet& mp1, const MappingSet& mp2) {
        if (mp1.size() != mp2.size()) {
            return false;
        }

        for (size_t i = 0; i < mp1.size(); i++) {
            if (mp1[i].first != mp2[i].first) {
                return false;
            }

            if (mp1[i].second != mp2[i].second) {
                return false;
            }
        }
        return true;
    }

    bool inResult(const MappingSet& state) {
        for (MappingSet res : results) {
            for (int i = 0; i < state.size(); i++) {
                if (MappingsEq(res, state)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isResult(const MappingSet& state) {
        for (Mapping p1 : state) {
            for (Mapping p2 : state) {
                if (g1.isVertexConneted(p1.first, p2.first) != g2.isVertexConneted(p1.second, p2.second)) {
                    return false;
                }
            }
        }

        // 因为是无向图算法可能产生重复解
        return !inResult(state);
    }
};