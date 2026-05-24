
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
#define MAXV 1001

class Graph
{
private:
	int n; // number of peaks
	int m; // number of edges

	vector<int> adj[MAXV]; //adjacency list
	int a[MAXV][MAXV]; //matrix adjacency
	vector<pair<int, int>> edge; // edge list

    // Helper functions to synchronize representations
    void syncFromMatrix();
    void syncFromEdgeList(bool isUndirected);
    void syncFromAdjList();

    // Recursive helper for DFS
    void DFS_helper(int u, vector<bool>& visited);

public:
    Graph(int x);
    void readMTK(string path);
    void readDSC(string path);
    void readDSK(string path);

    void writeMTK(string path);
    void writeDSC(string path);
    void writeDSK(string path);

    void printMTK();
    void printDSC();
    void printDSK();

    bool unDirected();

    int sumDeg();
    int deg(int i);

    int sumDegOut();
    int sumDegIn();

    int degOut(int i);
    int degIn(int i);

    // between any two vertices there is an edge (complete graph)
    bool isGraphFull();

    // graph contains only one cycle and passes through all vertices, each vertex has degree 2 (cycle graph)
    bool isGraphCycle(int u, vector<bool>& visited, int parent);
    bool isGraphCircle();

    // If there is an edge between two vertices of the same color, the graph is not bipartite
    bool isBipartite();

    void DFS(int i);
    void BFS(int i);

    void connectedComponent(int& tplt);

    // New algorithms and helper
    void readDSC_weighted(string path, bool isUndirected, int &s, int &t);
    void Euler(int v);
    void Kruskal();
    void Prim(int u);
    void Dijkstra(int s, int t);
};

#endif	