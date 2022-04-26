#include "../graph.h"
#include "state.h"
#include <vector>

using namespace std;

class VF2 {
public:
    Graph g1, g2; // 两个需要检测的图
    State s; // 状态

    vector<vector<Mapping>> results; // 结果集

    // 算法字段
    void getPs() { // 生成还可以再用来匹配的映射
        vector<char> Pred = G1.getPred();
        vector<char> succ = G1.getSucc();

        vector<char> out1Terminal = G1.getMsSucc(Ms);
        vector<char> in1Terminal = G1.getMsPred(Ms);

        vector<char> out2Terminal = G1.getMsSucc(Ms);
        vector<char> in2Terminal = G1.getMsPred(Ms);

        if (out1Terminal.size() > 0 && outT2terminal.size() > 0) {
            return out1Terminal x min(out2Terminal);
        }

        if (out1Terminal.size() == 0 && out2Terminal.size() == 0 && in1Terminal.size() > 0 && in2Terminal.size() > 0) {
            return in1Terminal x min(in2Terminal)
        }

        M1s = getM1S();
        M2s = getM2S();

        return (V1 - M1s) x min(V2 - M2s);
    }

    // feasiblity function
    bool F(Vector<char> s, char n, char m) { // 判断一对映射是否是匹配的点
        M1s = getM1S();
        M2s = getM2S();
        if (n in Ms1 && m in M2S) {
            for (char p : M1s) {
                for (char q : Ms2)
                    if (!pointMatch(p, n, q, m)) {
                        return false;
                    }
            }
            return true;
        }

        vector<char> out1Terminal = G1.getMsSucc(Ms);
        vector<char> in1Terminal = G1.getMsPred(Ms);

        vector<char> out2Terminal = G1.getMsSucc(Ms);
        vector<char> in2Terminal = G1.getMsPred(Ms);

        vector<char> v1 = V1 - M1s - in1Terminal - out1Terminal;

        vector<char> v2 = V2 - M2s - in2Terminal - out2Terminal;

        if (
            in1Terminal.size() <= in2Terminal.size()
            && out1Terminal.size() <= out2Terminal.size()
            && v1.size() <= v2.size()) {
            return true;
        }

        return false;
    }

    void add(n, m) {
        Ms.push(Pair(n, m));

        return {n, m};
    }

    bool match() {
        if (s.M.size() == g2.V.size()) { // 这里不会修改s
            output(Ms);
            return true;
        }

        Ps = getPs(Ms);
        for (each(n, m) : Ps) {
            if F (s, n, m) {
                s1 = add(n, m); // 这里会修改s
                Match(s1);
            }
        }
        restore(s);
    }
};