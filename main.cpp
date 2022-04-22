#include "demo.h"
#include "graph.h"

using namespace std;

int main() {
    // Graph g = Demo1::getBigGraph();
    // Demo1::resultDisplay("end point test", g.getEndPoints({'2', '3', '6'}));

    // // printf("%d", g.G[2][1]);
    // // g.display("big graph");

    // VType p3 = Demo1::getP3();
    // Graph gP3 = g.subGraph(p3);
    // gP3.display("matched p3");

    Demo1::resultDisplay("test 2 3 6", Demo1::test236());
    Demo1::resultDisplay("test 2 4 5", Demo1::test245());
}