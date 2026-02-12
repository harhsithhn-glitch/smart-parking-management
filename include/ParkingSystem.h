#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ParkingSlot.h"

class ParkingSystem {
private:
    std::vector<ParkingSlot> slots;

    // SAFE INDEXING (plate -> slot index)
    std::unordered_map<std::string, int> vehicleIndex;

    double totalRevenue;
    const std::string adminPassword = "elite123";

    double getRate(VehicleType type);

public:
    ParkingSystem(int floors, int slotsPerFloor);

    void showStatus();
    void parkVehicle();
    void removeVehicle();
    void adminPanel();
};

#endif