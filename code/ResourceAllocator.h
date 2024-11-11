#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H

#include <vector>
#include <string>

// Base struct for common attributes
struct Resource {
    std::string type;
    int district;
    double cost;
    double importance;
    double availability;
};

// Extended attributes for specific resource types
struct Electricity : public Resource {
    double peakDemandMW;
    double avgDemandMW;
};

struct Water : public Resource {
    double waterQualityPH;
};

struct Gas : public Resource {
    double gasPressureKPa;
};

struct WasteManagement : public Resource {};

// ResourceAllocator class
class ResourceAllocator {
private:
    std::vector<Electricity> electricityResources;
    std::vector<Water> waterResources;
    std::vector<Gas> gasResources;
    std::vector<WasteManagement> wasteManagementResources;

public:
    explicit ResourceAllocator(const std::string& file);
    void allocateResources();
    void displayAllocation() const;

private:
    void loadResources(const std::string& file);
    void allocateElectricity();
    void allocateWater();
    void allocateGas();
    void allocateWasteManagement();
};

#endif // RESOURCE_ALLOCATOR_H

