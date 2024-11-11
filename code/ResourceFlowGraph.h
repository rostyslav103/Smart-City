#ifndef RESOURCE_FLOW_GRAPH_H
#define RESOURCE_FLOW_GRAPH_H

#include <vector>

struct Edge {
    int to;
    double capacity;
};

class ResourceFlowGraph {
private:
    std::vector<std::vector<Edge>> adjList;

public:
    explicit ResourceFlowGraph(int n);
    void addEdge(int from, int to, double capacity);
};

#endif // RESOURCE_FLOW_GRAPH_H