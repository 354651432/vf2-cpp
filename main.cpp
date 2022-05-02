#include <cstdio>
#include <fstream>
#include <iostream>

#include "graph-fromjson.hpp"
#include "vf2.hpp"

using namespace std;

int main(int argc, char const* argv[]) {

    auto g1 = graphFromJsonFile("../graph-data/graph1.json");
    auto g2 = graphFromJsonFile("../graph-data/p6.json");

    auto results = Vf2<string>::runV2f(*g1, *g2);

    if (results.size() <= 0) {
        cout << "no results";
        return 0;
    }

    int cnt = 0;
    cout << "graph " << g1->title << " is sub matched graph " << g2->title << endl
         << endl;
    for (auto result : results) {
        cout << "result:" << ++cnt << endl;
        for (auto pr : result) {
            cout << " " << pr.first << " -> " << pr.second << endl;
        }
        cout << endl;
    }

    return 0;
}
