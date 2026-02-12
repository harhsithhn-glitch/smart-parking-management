#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, VehicleType t)
    : plateNumber(plate), type(t) {
    entryTime = std::chrono::system_clock::now();
}

std::string Vehicle::getPlateNumber() const {
    return plateNumber;
}

VehicleType Vehicle::getType() const {
    return type;
}

double Vehicle::calculateHoursParked() const {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = now - entryTime;

    double hours = diff.count() / 3600.0;

    if (hours < 1.0)
        return 1.0;

    return hours;
}