#include "../include/Vehicle.h"

Vehicle::Vehicle(const std::string& plateNumber, VehicleType vehicleType)
    : plate(plateNumber), type(vehicleType), entryTime(std::time(nullptr))
{
}
