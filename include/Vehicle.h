#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

enum class VehicleType {
    CAR = 1,
    BIKE = 2,
    TRUCK = 3
};

class Vehicle {
private:
    std::string plateNumber;
    VehicleType type;

public:
    Vehicle(std::string plate = "", VehicleType t = VehicleType::CAR);

    std::string getPlateNumber() const;
    VehicleType getType() const;
};

#endif