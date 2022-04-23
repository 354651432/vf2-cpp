#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> VType;
typedef vector<vector<int>> GType;

class Graph {
private:
public:
    Graph();
    void display(string);
    void display();
    Graph subGraph(VType);
    int getVPoint(char x);
    int getPoint(char x, char y);

    bool inPoint(char x);

    // get p3 ext point
    VType C4(VType);

    VType V;
    GType G;

    VType getEndPoints(VType);
};