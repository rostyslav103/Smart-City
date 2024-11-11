#include "ResourceAllocator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

ResourceAllocator::ResourceAllocator(const string& file) {
    loadResources(file);
}

void ResourceAllocator::loadResources(const string& file) {
    ifstream inFile(file);
    string line, type;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string type, districtStr, costStr, importanceStr, availabilityStr, peakDemandStr, avgDemandStr, waterQualityStr, gasPressureStr;

        getline(ss, type, '\t');
        getline(ss, districtStr, '\t');
        getline(ss, costStr, '\t');
        getline(ss, importanceStr, '\t');
        getline(ss, availabilityStr, '\t');
        getline(ss, peakDemandStr, '\t');
        getline(ss, avgDemandStr, '\t');
        getline(ss, waterQualityStr, '\t');
        getline(ss, gasPressureStr, '\t');

        int district = stoi(districtStr);
        double cost = stod(costStr);
        double importance = stod(importanceStr);
        double availability = stod(availabilityStr);

        if (type == "Electricity") {
            double peakDemand = stod(peakDemandStr);
            double avgDemand = stod(avgDemandStr);
            electricityResources.push_back({type, district, cost, importance, availability, peakDemand, avgDemand});
        } else if (type == "Water") {
            double waterQuality = stod(waterQualityStr);
            waterResources.push_back({type, district, cost, importance, availability, waterQuality});
        } else if (type == "Gas") {
            double gasPressure = stod(gasPressureStr);
            gasResources.push_back({type, district, cost, importance, availability, gasPressure});
        } else if (type == "Waste management") {
            wasteManagementResources.push_back({type, district, cost, importance, availability});
        }
    }
}

void ResourceAllocator::allocateResources() {
    allocateElectricity();
    allocateWater();
    allocateGas();
    allocateWasteManagement();
}

void ResourceAllocator::allocateElectricity() {
    sort(electricityResources.begin(), electricityResources.end(), [](const Electricity& a, const Electricity& b) {
        return a.peakDemandMW > b.peakDemandMW;
    });

    for (auto& e : electricityResources) {
        e.availability -= min(e.availability, e.peakDemandMW);
    }
}

void ResourceAllocator::allocateWater() {
    for (auto& w : waterResources) {
        w.availability -= 10;
    }
}

void ResourceAllocator::allocateGas() {
    for (auto& g : gasResources) {
        g.availability -= 50;
    }
}

void ResourceAllocator::allocateWasteManagement() {
    for (auto& wm : wasteManagementResources) {
        wm.availability -= 5;
    }
}

void ResourceAllocator::displayAllocation() const {
    cout << "Electricity Allocation Results:\n";
    for (const auto& e : electricityResources) {
        cout << "District " << e.district << ": Remaining Availability: " << e.availability << " MW\n";
    }

    cout << "\nWater Allocation Results:\n";
    for (const auto& w : waterResources) {
        cout << "District " << w.district << ": Remaining Availability: " << w.availability << " units\n";
    }

    cout << "\nGas Allocation Results:\n";
    for (const auto& g : gasResources) {
        cout << "District " << g.district << ": Remaining Availability: " << g.availability << " kPa\n";
    }

    cout << "\nWaste Management Allocation Results:\n";
    for (const auto& wm : wasteManagementResources) {
        cout << "District " << wm.district << ": Remaining Availability: " << wm.availability << " tons\n";
    }
}
