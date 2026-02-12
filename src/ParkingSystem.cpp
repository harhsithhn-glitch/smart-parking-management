#include "../include/ParkingSystem.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

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

double ParkingSystem::getRate(VehicleType type) {
    switch(type) {
        case VehicleType::BIKE:  return 15;
        case VehicleType::CAR:   return 30;
        case VehicleType::TRUCK: return 60;
    }
    return 0;
}

void ParkingSystem::logEvent(const string& message) {
    ofstream log("data/system_log.txt", ios::app);
    time_t now = time(nullptr);
    log << ctime(&now) << " - " << message << "\n";
}

void ParkingSystem::showStatus() {
    cout << "\n===== Parking Status =====\n";
    for(auto &slot : slots) {
        cout << "Floor " << slot.floor
             << " | Slot " << slot.number << " : ";
        if(slot.occupied)
            cout << "Occupied (" << slot.vehicle->plate << ")";
        else
            cout << "Empty";
        cout << endl;
    }
}

void ParkingSystem::parkVehicle() {
    string plate;
    int typeInput;

    cout << "Enter plate number: ";
    cin >> plate;

    if(vehicleIndex.count(plate)) {
        cout << "Vehicle already parked!\n";
        return;
    }

    cout << "Vehicle Type (1=Bike, 2=Car, 3=Truck): ";
    cin >> typeInput;

    VehicleType type = static_cast<VehicleType>(typeInput);

    for(auto &slot : slots) {
        if(!slot.occupied) {
            slot.vehicle = make_shared<Vehicle>(plate, type);
            slot.occupied = true;
            vehicleIndex[plate] = &slot;

            cout << "Parked at Floor "
                 << slot.floor << ", Slot "
                 << slot.number << endl;

            logEvent("Vehicle Parked: " + plate);
            saveData();
            return;
        }
    }

    cout << "Parking Full!\n";
}

void ParkingSystem::removeVehicle() {
    string plate;
    cout << "Enter plate number: ";
    cin >> plate;

    if(!vehicleIndex.count(plate)) {
        cout << "Vehicle not found!\n";
        return;
    }

    ParkingSlot* slot = vehicleIndex[plate];
    time_t exitTime = time(nullptr);

    double hours = difftime(exitTime,
                    slot->vehicle->entryTime) / 3600.0;
    if(hours < 1) hours = 1;

    double fee = hours * getRate(slot->vehicle->type);
    totalRevenue += fee;

    cout << fixed << setprecision(2);
    cout << "Removed from Floor "
         << slot->floor << ", Slot "
         << slot->number << endl;
    cout << "Fee: ₹" << fee << endl;

    exportRevenueCSV(plate, fee);

    slot->vehicle = nullptr;
    slot->occupied = false;
    vehicleIndex.erase(plate);

    logEvent("Vehicle Removed: " + plate);
    saveData();
}

void ParkingSystem::adminPanel() {
    string pass;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if(pass != adminPassword) {
        cout << "Access Denied!\n";
        return;
    }

    cout << "\n===== ADMIN PANEL =====\n";
    cout << "Total Revenue: ₹"
         << fixed << setprecision(2)
         << totalRevenue << endl;
}

void ParkingSystem::exportRevenueCSV(const string& plate, double fee) {
    ofstream csv("data/revenue_report.csv", ios::app);
    time_t now = time(nullptr);
    csv << plate << ","
        << fee << ","
        << ctime(&now);
}

void ParkingSystem::saveData() {
    ofstream file("data/parking_data.txt");
    for(auto &slot : slots) {
        if(slot.occupied) {
            file << slot.floor << " "
                 << slot.number << " "
                 << slot.vehicle->plate << " "
                 << static_cast<int>(slot.vehicle->type) << " "
                 << slot.vehicle->entryTime << endl;
        }
    }
    file << "REVENUE " << totalRevenue;
}

void ParkingSystem::loadData() {
    ifstream file("data/parking_data.txt");
    if(!file) return;

    string plate, tag;
    int f, s, type;
    time_t entry;

    while(file >> f) {
        if(f == 0) break;
        file >> s >> plate >> type >> entry;

        for(auto &slot : slots) {
            if(slot.floor == f && slot.number == s) {
                slot.vehicle = make_shared<Vehicle>(
                    plate,
                    static_cast<VehicleType>(type)
                );
                slot.vehicle->entryTime = entry;
                slot.occupied = true;
                vehicleIndex[plate] = &slot;
            }
        }
    }

    if(file >> tag >> totalRevenue) {}
}