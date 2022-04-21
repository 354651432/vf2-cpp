#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Graph
{
public:
    Graph();
    void display();

    vector<char> V;
    vector<vector<int>> G;
};

Graph::Graph()
{
    this->V = vector<char>();
    this->G = vector<vector<int>>();
}

void Graph::display()
{
    printf("points:");
    for (auto c : this->V)
    {
        printf("%c,", c);
    }
    printf("\n");
    printf("\n");

    printf("matrix:");
    for (auto line : this->G)
    {
        for (auto p : line)
        {
            printf("%d,", p);
        }
        printf("\n");
    }
}

vector<Graph> f1(Graph *g1, Graph *g2)
{
    return vector<Graph>();
}

int main()
{
    Graph *g = new Graph();
    g->V.push_back('A');
    g->V.push_back('B');
    g->V.push_back('C');

    g->G.push_back(vector<int>{0, 1, 1});
    g->G.push_back(vector<int>{1, 0, 1});
    g->G.push_back(vector<int>{1, 1, 0});

    g->display();
}