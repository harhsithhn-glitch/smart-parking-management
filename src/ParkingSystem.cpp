#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "../include/ParkingSystem.h"
#include "../include/Vehicle.h"

using namespace std;

ParkingSystem::ParkingSystem(int floors, int slotsPerFloor)
    : totalRevenue(0.0) {

    for (int f = 1; f <= floors; ++f) {
        for (int s = 1; s <= slotsPerFloor; ++s) {
            slots.emplace_back(f, s);
        }
    }

    loadData();
}

double ParkingSystem::getRate(VehicleType type) {
    switch(type) {
        case VehicleType::CAR: return 20.0;
        case VehicleType::BIKE: return 10.0;
        case VehicleType::TRUCK: return 30.0;
        default: return 15.0;
    }
}

void ParkingSystem::logEvent(const string& message) {
    ofstream file("data/log.txt", ios::app);
    time_t now = time(0);
    file << ctime(&now) << " : " << message << "\n";
    file.close();
}

void ParkingSystem::saveData() {
    ofstream file("data/parking_data.txt");

    file << totalRevenue << "\n";

    for (const auto& slot : slots) {
        if (!slot.isAvailable()) {
            file << slot.getFloor() << " "
                 << slot.getSlotNumber() << " "
                 << slot.getVehicle().getPlateNumber() << " "
                 << static_cast<int>(slot.getVehicle().getType()) << "\n";
        }
    }

    file.close();
}

void ParkingSystem::loadData() {
    ifstream file("data/parking_data.txt");
    if (!file.is_open()) return;

    file >> totalRevenue;

    int floor, slotNumber, typeInt;
    string plate;

    while (file >> floor >> slotNumber >> plate >> typeInt) {
        for (auto& slot : slots) {
            if (slot.getFloor() == floor &&
                slot.getSlotNumber() == slotNumber) {

                Vehicle vehicle(plate, static_cast<VehicleType>(typeInt));
                slot.parkVehicle(vehicle);
                vehicleIndex[plate] = &slot;
                break;
            }
        }
    }

    file.close();
}

void ParkingSystem::exportRevenueCSV(const string& plate, double fee) {
    ofstream file("data/revenue.csv", ios::app);
    file << plate << "," << fixed << setprecision(2) << fee << "\n";
    file.close();
}

void ParkingSystem::showStatus() {
    cout << "\n===== PARKING STATUS =====\n";

    for (const auto& slot : slots) {
        cout << "Floor " << slot.getFloor()
             << " Slot " << slot.getSlotNumber()
             << " : ";

        if (slot.isAvailable())
            cout << "Available\n";
        else
            cout << "Occupied (" << slot.getVehicle().getPlateNumber() << ")\n";
    }

    cout << "Total Revenue: " << totalRevenue << "\n";
}

void ParkingSystem::parkVehicle() {
    string plate;
    int typeInput;

    cout << "Enter plate number: ";
    cin >> plate;

    if (vehicleIndex.count(plate)) {
        cout << "Vehicle already parked.\n";
        return;
    }

    cout << "Select type (1-Car, 2-Bike, 3-Truck): ";
    cin >> typeInput;

    VehicleType type = static_cast<VehicleType>(typeInput - 1);
    Vehicle vehicle(plate, type);

    for (auto& slot : slots) {
        if (slot.isAvailable()) {
            slot.parkVehicle(vehicle);
            vehicleIndex[plate] = &slot;

            logEvent("Vehicle parked: " + plate);
            saveData();

            cout << "Vehicle parked successfully.\n";
            return;
        }
    }

    cout << "Parking Full.\n";
}

void ParkingSystem::removeVehicle() {
    string plate;

    cout << "Enter plate number: ";
    cin >> plate;

    if (!vehicleIndex.count(plate)) {
        cout << "Vehicle not found.\n";
        return;
    }

    ParkingSlot* slot = vehicleIndex[plate];

    double fee = getRate(slot->getVehicle().getType());

    totalRevenue += fee;

    exportRevenueCSV(plate, fee);

    slot->removeVehicle();
    vehicleIndex.erase(plate);

    logEvent("Vehicle removed: " + plate);
    saveData();

    cout << "Vehicle removed.\n";
    cout << "Parking Fee: " << fee << "\n";
}

void ParkingSystem::adminPanel() {
    string password;

    cout << "Enter Admin Password: ";
    cin >> password;

    if (password != adminPassword) {
        cout << "Access Denied.\n";
        return;
    }

    int choice;

    cout << "\n--- ADMIN PANEL ---\n";
    cout << "1. View Revenue\n";
    cout << "2. Reset Revenue\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Total Revenue: " << totalRevenue << "\n";
    }
    else if (choice == 2) {
        totalRevenue = 0;
        saveData();
        cout << "Revenue reset.\n";
    }
}