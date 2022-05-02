#include "configor/json.h"
#include "graph.hpp"
#include <fstream>
#include <memory>
#include <vector>

using namespace std;

auto graphFromJsonFile(const string& filename) {
    configor::json json;
    ifstream hf(filename);
    hf >> json;
    hf.close();

    auto g = make_unique<Graph<string>>();

    g->title = (string)json["title"];
    for (string str : json["V"]) {
        g->V.push_back(str);
    }

    for (auto arr : json["G"]) {
        vector<int> line;
        for (int it : arr) {
            line.push_back(it);
        }
        g->G.push_back(line);
    }

    return move(g);
}