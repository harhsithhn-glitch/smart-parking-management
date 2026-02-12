#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>

enum class VehicleType { BIKE = 1, CAR, TRUCK };

class Vehicle {
public:
    std::string plate;
    VehicleType type;
    std::time_t entryTime;

    Vehicle(const std::string& plateNumber, VehicleType vehicleType);
};

#endif