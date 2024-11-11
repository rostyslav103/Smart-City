#include "ResourceFlowGraph.h"

ResourceFlowGraph::ResourceFlowGraph(int n) : adjList(n) {}

void ResourceFlowGraph::addEdge(int from, int to, double capacity) {
    adjList[from].push_back({to, capacity});
    adjList[to].push_back({from, 0}); // Reverse edge
}