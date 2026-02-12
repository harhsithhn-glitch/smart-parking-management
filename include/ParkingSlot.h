#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <memory>
#include "Vehicle.h"

class ParkingSlot {
public:
    int floor;
    int number;
    bool occupied;
    std::shared_ptr<Vehicle> vehicle;

    ParkingSlot(int floorNumber, int slotNumber);
};

#endif
