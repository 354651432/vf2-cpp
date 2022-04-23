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
    Graph(VType v, GType g);
    Graph subGraph(VType);
    int getVPoint(char x);
    int getPoint(char x, char y);

    bool inPoint(char x);

    string title;
    VType V;
    GType G;

    VType getEndPoints(VType);

    void validate();

    static Graph fromJson(string filename);
};