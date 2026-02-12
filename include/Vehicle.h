#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <chrono>

enum class VehicleType {
    CAR = 1,
    BIKE,
    TRUCK
};

class Vehicle {
private:
    std::string plateNumber;
    VehicleType type;
    std::chrono::system_clock::time_point entryTime;

public:
    Vehicle(std::string plate, VehicleType t);

    std::string getPlateNumber() const;
    VehicleType getType() const;

    double calculateHoursParked() const;
};

#endif