#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include "Vehicle.h"

class ParkingSlot {
private:
    int floor;
    int slotNumber;
    bool available;
    Vehicle vehicle;

public:
    ParkingSlot(int f, int s);

    bool isAvailable() const;
    void parkVehicle(const Vehicle& v);
    void removeVehicle();

    int getFloor() const;
    int getSlotNumber() const;
    Vehicle getVehicle() const;
};

#endif