#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ParkingSlot.h"

class ParkingSystem {
private:
    std::vector<ParkingSlot> slots;
    std::unordered_map<std::string, ParkingSlot*> vehicleIndex;

    double totalRevenue;
    const std::string adminPassword = "elite123";

    double getRate(VehicleType type);
    void logEvent(const std::string& message);
    void saveData();
    void loadData();
    void exportRevenueCSV(const std::string& plate, double fee);

public:
    ParkingSystem(int floors, int slotsPerFloor);

    void showStatus();
    void parkVehicle();
    void removeVehicle();
    void adminPanel();
};

#endif
