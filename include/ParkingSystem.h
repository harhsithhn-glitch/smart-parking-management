#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ParkingSlot.h"

class ParkingSystem {
private:
    std::vector<ParkingSlot> slots;
    std::unordered_map<std::string, size_t> vehicleIndex;

    double totalRevenue;

    static constexpr double BIKE_RATE = 20.0;
    static constexpr double CAR_RATE = 50.0;
    static constexpr double TRUCK_RATE = 100.0;

    static constexpr int MAX_PLATE_LENGTH = 15;

    double getRate(VehicleType type) const;
    bool isValidPlate(const std::string& plate) const;
    bool isValidVehicleType(int type) const;
    void logEvent(const std::string& message) const;
    void saveData() const;
    void loadData();

public:
    ParkingSystem(int floors, int slotsPerFloor);

    void showStatus() const;
    void parkVehicle();
    void removeVehicle();
    void searchVehicle() const;
    void adminPanel() const;
};

#endif