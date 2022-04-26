#include "state.h"

int main(int argc, char const* argv[]) {
    Graph g1 = Graph::fromJson("../graph-data/p3.json");
    Graph g2 = Graph::fromJson("../graph-data/p3.json");

    State s(g1, g2);
    bool result = s.vf2();
    std::cout << "result:" << result << std::endl;

    return 0;
}
