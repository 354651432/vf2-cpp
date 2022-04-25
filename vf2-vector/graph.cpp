#include "graph.h"
#include <iostream>
void GraphVec::addedge(int u, int v, int w) {
    pred[v].insert(u);
    succ[u].insert(v);

    edge[en].v = v;
    edge[en].w = w;
    edge[en].next = head[u];
    head[u] = en;

    swap(u, v);
    redge[en].v = v;
    redge[en].w = w;
    redge[en].next = rhead[u];
    rhead[u] = en++;
}

GraphVec::GraphVec(int _n, int _e) {
    en = 0;
    n = _n;
    e = _e;
    head.resize(n);
    rhead.resize(n);

    pred.resize(n);
    succ.resize(n);

    node.resize(n);

    edge.resize(e);
    redge.resize(e);
    fill(head.begin(), head.end(), -1);
    fill(rhead.begin(), rhead.end(), -1);
}
void GraphVec::initGraph(Container *cnode, Container *cedge) {
    int u, v, w;
    for (int i = 0; i < n; ++i) {
        u = cnode[i].a;
        w = cnode[i].b;
        node[u] = w;
    }
    for (int i = 0; i < e; ++i) {
        u = cedge[i].a;
        v = cedge[i].b;
        w = cedge[i].c;
        addedge(u, v, w);
    }
}


int GraphVec::getSize()const {
    return n;
}
int GraphVec::getNodeLabel(int i)const {
    return node[i];
}
int GraphVec::getHead(int i)const {
    if (head[i] < -10) {cout<<i<<" "<<head[i]<<endl;}
    return head[i];
}
int GraphVec::getRhead(int i) const {
    if (rhead[i] < -10) {cout<<i<<" "<<rhead[i]<<endl;}
    return rhead[i];
}