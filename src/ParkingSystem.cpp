#include "../include/ParkingSystem.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

// Constructor
ParkingSystem::ParkingSystem(int floors, int slotsPerFloor)
    : totalRevenue(0)
{
    for(int f = 1; f <= floors; f++) {
        for(int s = 1; s <= slotsPerFloor; s++) {
            slots.emplace_back(f, s);
        }
    }

    loadData();
}