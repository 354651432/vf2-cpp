#include "state.h"

int main(int argc, char const* argv[]) {
    Graph g1 = Graph::fromJson("../graph-data/t2.json");
    Graph g2 = Graph::fromJson("../graph-data/t1.json");

    State s(g1, g2);
    int result = s.vf2(vector<Mapping> {});

    std::cout << "result:" << result << std::endl;

    int i = 0;
    for (auto M : s.results) {
        cout << "result: " << ++i << endl;
        for (auto pars : M) {
            std::cout << pars.first << "->" << pars.second << std::endl;
        }
        cout << endl;
    }

    return 0;
}
