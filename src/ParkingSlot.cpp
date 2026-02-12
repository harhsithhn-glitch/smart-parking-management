#include "ParkingSlot.h"

ParkingSlot::ParkingSlot(int f, int s)
    : floor(f), slotNumber(s), available(true),
      vehicle("", VehicleType::CAR) {}

bool ParkingSlot::isAvailable() const {
    return available;
}

void ParkingSlot::parkVehicle(const Vehicle& v) {
    vehicle = v;
    available = false;
}

void ParkingSlot::removeVehicle() {
    available = true;
}

int ParkingSlot::getFloor() const {
    return floor;
}

int ParkingSlot::getSlotNumber() const {
    return slotNumber;
}

Vehicle ParkingSlot::getVehicle() const {
    return vehicle;
}