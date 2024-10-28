#include <iostream>
#include <vector>
using namespace std;

// Struct to represent the resource metadata
struct Resource {
    string name;           // Type of resource
    double cost;           // Cost per unit
    double importance;     // Priority factor (higher is more important)
    double availableUnits; // Total units available
};

// Struct to represent the sector metadata
struct Sector {
    string name;              // Type of sector
    double requiredUnits;     // Total units needed
    double allocatedUnits;    // Units allocated
    vector<string> resourcePreferences; // Ordered list of preferred resources
};

// Struct to represent each edge of the graph
struct Edge {
    int to;
    double capacity;
};

// Class to manage resources and allocation
class ResourceAllocator {
    vector<Sector> sectors;
    vector<Resource> resources;
public:
    // Constructor to initialize sectors and resources
    ResourceAllocator(const vector<Sector>& sectors, const vector<Resource>& resources)
            : sectors(sectors), resources(resources) {}

    // Assign resources to sectors based on availability and priority (greedy algorithm)
    void allocateResources() {
        // Sort sectors by requiredUnits using selection sort
        for (int i = 0; i < sectors.size(); ++i) {
            int maxIndex = i;
            for (int j = i + 1; j < sectors.size(); ++j) {
                if (sectors[j].requiredUnits > sectors[maxIndex].requiredUnits) {
                    maxIndex = j;
                }
            }
            if (maxIndex != i) {
                swap(sectors[i], sectors[maxIndex]);
            }
        }

        // Allocate resources to sectors
        for (auto & sector : sectors) {
            for (int j = 0; j < sector.resourcePreferences.size(); ++j) {
                const string& preferredResource = sector.resourcePreferences[j];

                // Search to find the preferred resource
                auto resourceCur = resources.end();
                for (int k = 0; k < resources.size(); ++k) {
                    if (resources[k].name == preferredResource) {
                        resourceCur = resources.begin() + k;
                        break;
                    }
                }

                if (resourceCur != resources.end() && resourceCur->availableUnits > 0) {
                    double allocatable = min(resourceCur->availableUnits, sector.requiredUnits);
                    resourceCur->availableUnits -= allocatable;
                    sector.allocatedUnits += allocatable;
                    sector.requiredUnits -= allocatable;

                    if (sector.requiredUnits <= 0) {
                        break;
                    }
                }
            }
        }
    }

    // Display allocation results
    void displayAllocation() const {
        cout << "Resource Allocation Results:\n";
        for (const auto & sector : sectors) {
            cout << "Sector: " << sector.name << ", Allocated Units: " << sector.allocatedUnits
                 << ", Remaining Requirement: " << sector.requiredUnits << "\n";
        }

        cout << "Remaining Resource Availability:\n";
        for (const auto & resource : resources) {
            cout << "Resource: " << resource.name << ", Available Units: " << resource.availableUnits << "\n";
        }
    }
};

// Class to represent a graph for resource flow
class ResourceFlowGraph {
    vector<vector<Edge>> adjList;
public:
    explicit ResourceFlowGraph(int n) : adjList(n) {}

    void addEdge(int from, int to, double capacity) {
        adjList[from].push_back({to, capacity});
        adjList[to].push_back({from, 0}); // Reverse edge for flow adjustment
    }
};

int main() {
    // Resource and sector test data
    vector<Resource> resources = {
            {"Water", 10, 0.9, 1000},
            {"Electricity", 20, 0.8, 500},
            {"Gas", 15, 0.7, 300}
    };

    vector<Sector> sectors = {
            {"Household", 400, 0, {"Water", "Electricity"}},
            {"Business", 600, 0, {"Electricity", "Gas"}},
            {"Industrial", 800, 0, {"Gas", "Water"}}
    };

    // Allocation example
    ResourceAllocator allocator(sectors, resources);
    allocator.allocateResources();
    allocator.displayAllocation();

    // Graph setup example
    ResourceFlowGraph flowGraph(5);
    flowGraph.addEdge(0, 1, 10);
    flowGraph.addEdge(1, 2, 5);

    cout << "Resource Allocation and Flow complete.\n";
    return 0;
}

