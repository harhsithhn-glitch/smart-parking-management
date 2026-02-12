#include <iostream>
#include "ParkingSystem.h"

using namespace std;

ParkingSystem::ParkingSystem(int floors, int slotsPerFloor)
    : totalRevenue(0.0) {

    for (int f = 1; f <= floors; f++) {
        for (int s = 1; s <= slotsPerFloor; s++) {
            slots.emplace_back(f, s);
        }
    }
}

double ParkingSystem::getRate(VehicleType type) {
    switch (type) {
        case VehicleType::CAR: return 50;
        case VehicleType::BIKE: return 20;
        case VehicleType::TRUCK: return 100;
        default: return 0;
    }
}

void ParkingSystem::showStatus() {
    for (const auto& slot : slots) {
        cout << "Floor " << slot.getFloor()
             << " Slot " << slot.getSlotNumber() << " : ";

        if (slot.isAvailable()) {
            cout << "Available\n";
        } else {
            cout << "Occupied ("
                 << slot.getVehicle().getPlateNumber()
                 << ")\n";
        }
    }
}

void ParkingSystem::parkVehicle() {
    string plate;
    int typeChoice;

    cout << "Enter Plate Number: ";
    cin >> plate;

    if (vehicleIndex.find(plate) != vehicleIndex.end()) {
        cout << "Vehicle already parked!\n";
        return;
    }

    cout << "Vehicle Type (0=Car,1=Bike,2=Truck): ";
    cin >> typeChoice;

    VehicleType type = static_cast<VehicleType>(typeChoice);
    Vehicle vehicle(plate, type);

    for (int i = 0; i < slots.size(); i++) {
        if (slots[i].isAvailable()) {
            slots[i].parkVehicle(vehicle);

            // SAFE STORAGE (Step 1 & 2)
            vehicleIndex[plate] = i;

            cout << "Parked at Floor "
                 << slots[i].getFloor()
                 << " Slot "
                 << slots[i].getSlotNumber()
                 << endl;

            return;
        }
    }

    cout << "Parking Full!\n";
}

void ParkingSystem::removeVehicle() {
    string plate;

    cout << "Enter Plate Number: ";
    cin >> plate;

    if (vehicleIndex.find(plate) == vehicleIndex.end()) {
        cout << "Vehicle not found!\n";
        return;
    }

    int index = vehicleIndex[plate];
    ParkingSlot& slot = slots[index];

    double fee = getRate(slot.getVehicle().getType());
    totalRevenue += fee;

    slot.removeVehicle();
    vehicleIndex.erase(plate);

    cout << "Vehicle removed. Fee: " << fee << endl;
}

void ParkingSystem::adminPanel() {
    string pass;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if (pass != adminPassword) {
        cout << "Access Denied!\n";
        return;
    }

    cout << "Total Revenue: " << totalRevenue << endl;
}
void ParkingSystem::searchVehicle() {
    std::string plate;
    std::cout << "Enter plate number to search: ";
    std::cin >> plate;

    auto it = vehicleIndex.find(plate);

    if (it == vehicleIndex.end()) {
        std::cout << "Vehicle not found.\n";
        return;
    }

    int index = it->second;
    ParkingSlot& slot = slots[index];

    std::cout << "Vehicle Found!\n";
    std::cout << "Floor: " << slot.getFloor() << "\n";
    std::cout << "Slot: " << slot.getSlotNumber() << "\n";
    std::cout << "Plate: " << slot.getVehicle().getPlateNumber() << "\n";
}