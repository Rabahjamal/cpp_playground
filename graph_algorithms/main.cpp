#include "dijkstra.h"

#include <iostream>

using namespace std;

int main()
{

    map<string, vector<pair<string, int>>> graph;

    graph.insert({"A", {{"B", 5}, {"C", 3}}});

    graph.insert({"B", {{"E", 4}}});

    graph.insert({"C", {{"B", 1}, {"D", 7}, {"F", 8}}});

    graph.insert({"D", {{"F", 3}}});

    graph.insert({"E", {{"F", 1}}});

    graph.insert({"F", vector<pair<string, int>>()});

    cout << Dijkstra::find_shortest_path(graph, string("A"), string("F")) << endl;

}
