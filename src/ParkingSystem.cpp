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
// Rate calculation
double ParkingSystem::getRate(VehicleType type) {
    switch(type) {
        case VehicleType::BIKE:  return 15;
        case VehicleType::CAR:   return 30;
        case VehicleType::TRUCK: return 60;
    }
    return 0;
}

// Logging system
void ParkingSystem::logEvent(const string& message) {
    ofstream log("data/system_log.txt", ios::app);
    time_t now = time(nullptr);
    log << ctime(&now) << " - " << message << "\n";
    log.close();
}