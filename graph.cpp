#include "graph.h"
#include <algorithm>
#include <string>

vector<Graph> match(Graph* g1, Graph* g2) {
    return vector<Graph>();
}

Graph::Graph() {
    this->V = vector<char>();
    this->G = vector<vector<int>>();
}

Graph::Graph(VType V, GType G)
    : V(V)
    , G(G) { }

int Graph::getVPoint(char x) {
    for (int i = 0; i < this->V.size(); i++) {
        if (this->V[i] == x) {
            return i;
        }
    }

    throw "point is not in the graph";
}

int Graph::getPoint(char x, char y) {
    int vx = this->getVPoint(x);
    int vy = this->getVPoint(y);

    return this->G[vx][vy];
}

bool Graph::inPoint(char x) {
    return this->getVPoint(x) != -1;
}

Graph Graph::subGraph(VType points) {
    Graph g;
    g.V = points;
    GType subG;
    for (auto x : points) {
        vector<int> line;
        for (auto y : points) {
            line.push_back(this->getPoint(x, y));
        }
        subG.push_back(line);
    }
    g.G = subG;

    return g;
}

void Graph::validate() {
    int n = this->V.size();

    // 对角线应该全部为0
    for (int i = 0; i < n; i++) {
        if (this->G[i][i] != 0) {
            throw string() + "[" + to_string(i) + "," + to_string(i) + "] should be 0";
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (this->G[i][j] != this->G[j][i]) {
                throw string() + "[" + to_string(i) + "," + to_string(j) + "] not eq to [" + to_string(j) + "," + to_string(i) + "]";
            }
        }
    }
}