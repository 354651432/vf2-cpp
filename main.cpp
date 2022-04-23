#include "configor/json.hpp"
#include "demo.h"
#include "graph.h"
#include <fstream>

class A {
public:
    string str = "fdsfd";
    char c;
};

int main() {
    // Demo1::testC4();
    // Demo1::testK13();
    // Demo1::testK14();
    // Demo1::testMatch();

    auto p3 = Graph::fromJson("graph-data/p3.json");
    Demo1::showGraph(p3);
}