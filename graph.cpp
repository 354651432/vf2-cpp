#include "graph.h"
#include <algorithm>

vector<Graph> match(Graph* g1, Graph* g2) {
    return vector<Graph>();
}

Graph::Graph() {
    this->V = vector<char>();
    this->G = vector<vector<int>>();
}

void Graph::display() {
    this->display("");
}
void Graph::display(string msg) {
    cout << msg << endl
         << "points:" << endl;
    for (auto c : this->V) {
        printf(" %c,", c);
    }
    printf("\n");

    printf("matrix:\n");
    for (auto line : this->G) {
        for (auto p : line) {
            printf(" %d,", p);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

int Graph::getVPoint(char x) {
    for (int i = 0; i < this->V.size(); i++) {
        if (this->V[i] == x) {
            return i;
        }
    }

    return -1;
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

// 找到顶点
VType Graph::getEndPoints(VType points) {
    if (this->getPoint(points[0], points[1]) == 1 && this->getPoint(points[0], points[2]) == 1) {
        return vector<char> {points[1], points[2]};
    }

    if (this->getPoint(points[0], points[1]) == 1 && this->getPoint(points[1], points[2]) == 1) {
        return vector<char> {points[0], points[2]};
    }

    return vector<char> {points[0], points[1]};
}

VType Graph::getP3Match(VType points) {
    VType result;
    VType endpoints = this->getEndPoints(points);
    for (char i : this->V) {
        if (find(points.begin(), points.end(), i) != points.end()) {
            continue;
        }

        if (this->getPoint(i, endpoints[0]) == 1 && this->getPoint(i, endpoints[1]) == 1) {
            result.push_back(i);
        }
    }

    return result;
}