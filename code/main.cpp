#include <iostream>
#include "ResourceAllocator.h"
#include "ResourceFlowGraph.h"

using namespace std;

int main() {
    string dataFile = "resources_data.csv";

    ResourceAllocator allocator(dataFile);
    allocator.allocateResources();
    allocator.displayAllocation();

    ResourceFlowGraph flowGraph(5);
    flowGraph.addEdge(0, 1, 10);
    flowGraph.addEdge(1, 2, 5);

    cout << "Resource Allocation and Flow complete.\n";
    return 0;
    return 0;
}

