#include "configor/json.h"
#include "graph.h"
#include <fstream>

Graph Graph::fromJson(string filename) {
    configor::json json;
    ifstream hf(filename);
    hf >> json;

    Graph g;
    g.title = json["title"];
    for (string str : json["V"]) {
        g.V.push_back(str.at(0));
    }

    for (auto arr : json["G"]) {
        vector<int> line;
        for (int it : arr) {
            line.push_back(it);
        }
        g.G.push_back(line);
    }

    return g;
}