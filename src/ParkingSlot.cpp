#include "../include/ParkingSlot.h"

ParkingSlot::ParkingSlot(int floorNumber, int slotNumber)
    : floor(floorNumber),
      number(slotNumber),
      occupied(false),
      vehicle(nullptr)
{
}