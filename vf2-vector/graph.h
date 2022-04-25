#ifndef VF2_GRAPH_H
#define VF2_GRAPH_H

#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;
const int MAXN = 305;

struct Edge {
    int v, w, next;
};
struct Container {
    int a, b, c;
};
class GraphVec {
private:
    vector<int> head;
    vector<int> rhead;
    int en; //edge number

public:
    vector<int> node;
    int n, e;
    void addedge(int u, int v, int w);

    int getNodeLabel(int i) const;
    void initGraph(Container* cnode, Container* cedge);
    int getSize() const;
    int getHead(int i) const;
    int getRhead(int i) const;
    vector<unordered_set<int>> pred, succ;
    vector<Edge> edge;
    vector<Edge> redge;
    GraphVec();
    GraphVec(int _n, int _e);
};

#endif //VF2_GRAPH_H
