#pragma once
#include "combination.h"
#include "graph.h"
#include "vf2-vector/graph.h"

bool graphEq(Graph g1, Graph g2);

vector<VType> match(Graph g1, Graph g2);

vector<VType> vf2(Graph g1, Graph g2);

GraphVec GraphVecFromGraph(Graph g);