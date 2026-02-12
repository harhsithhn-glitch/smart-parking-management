#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, VehicleType t)
    : plateNumber(plate), type(t) {}

std::string Vehicle::getPlateNumber() const {
    return plateNumber;
}

VehicleType Vehicle::getType() const {
    return type;
}