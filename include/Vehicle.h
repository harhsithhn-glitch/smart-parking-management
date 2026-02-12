#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class VehicleType {
    CAR = 0,
    BIKE = 1,
    TRUCK = 2
};

class Vehicle {
private:
    std::string plateNumber;
    VehicleType type;

public:
    Vehicle(std::string plate, VehicleType t);

    std::string getPlateNumber() const;
    VehicleType getType() const;
};

#endif