#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

enum VehicleType { BIKE = 1, CAR, TRUCK };

class Vehicle {
public:
    string plateNumber;
    VehicleType type;
    time_t entryTime;

    Vehicle(string plate, VehicleType t) {
        plateNumber = plate;
        type = t;
        entryTime = time(0);
    }
};

class ParkingSlot {
public:
    int floor;
    int slotNumber;
    bool isOccupied;
    Vehicle* vehicle;

    ParkingSlot(int f, int num) {
        floor = f;
        slotNumber = num;
        isOccupied = false;
        vehicle = nullptr;
    }
};

class ParkingSystem {
private:
    vector<ParkingSlot> slots;
    const string adminPassword = "admin123";
    double totalRevenue = 0;

    double getRate(VehicleType type) {
        if(type == BIKE) return 10;
        if(type == CAR) return 20;
        return 40;
    }

public:
    ParkingSystem(int floors, int slotsPerFloor) {
        for(int f = 1; f <= floors; f++) {
            for(int s = 1; s <= slotsPerFloor; s++) {
                slots.push_back(ParkingSlot(f, s));
            }
        }
        loadData();
    }

    void showStatus() {
        cout << "\n===== Parking Status =====\n";
        for(auto &slot : slots) {
            cout << "Floor " << slot.floor
                 << " | Slot " << slot.slotNumber << " : ";
            if(slot.isOccupied)
                cout << "Occupied (" << slot.vehicle->plateNumber << ")";
            else
                cout << "Empty";
            cout << endl;
        }
    }

    void parkVehicle() {
        string plate;
        int typeInput;

        cout << "Enter plate number: ";
        cin >> plate;

        cout << "Vehicle Type (1=Bike, 2=Car, 3=Truck): ";
        cin >> typeInput;

        VehicleType type = (VehicleType)typeInput;

        for(auto &slot : slots) {
            if(!slot.isOccupied) {
                slot.vehicle = new Vehicle(plate, type);
                slot.isOccupied = true;
                cout << "Parked at Floor " << slot.floor
                     << ", Slot " << slot.slotNumber << endl;
                saveData();
                return;
            }
        }

        cout << "Parking Full!\n";
    }

    void removeVehicle() {
        string plate;
        cout << "Enter plate number: ";
        cin >> plate;

        for(auto &slot : slots) {
            if(slot.isOccupied && slot.vehicle->plateNumber == plate) {

                time_t exitTime = time(0);
                double hours = difftime(exitTime,
                        slot.vehicle->entryTime) / 3600.0;
                if(hours < 1) hours = 1;

                double rate = getRate(slot.vehicle->type);
                double fee = hours * rate;
                totalRevenue += fee;

                cout << "Removed from Floor "
                     << slot.floor << ", Slot "
                     << slot.slotNumber << endl;
                cout << "Fee: ₹" << fee << endl;

                delete slot.vehicle;
                slot.vehicle = nullptr;
                slot.isOccupied = false;

                saveData();
                return;
            }
        }

        cout << "Vehicle not found!\n";
    }

    void adminPanel() {
        string pass;
        cout << "Enter Admin Password: ";
        cin >> pass;

        if(pass != adminPassword) {
            cout << "Access Denied!\n";
            return;
        }

        cout << "\n===== ADMIN PANEL =====\n";
        cout << "Total Revenue: ₹" << totalRevenue << endl;
    }

    void saveData() {
        ofstream file("parking_data.txt");
        for(auto &slot : slots) {
            if(slot.isOccupied) {
                file << slot.floor << " "
                     << slot.slotNumber << " "
                     << slot.vehicle->plateNumber << " "
                     << slot.vehicle->type << " "
                     << slot.vehicle->entryTime << endl;
            }
        }
        file.close();
    }

    void loadData() {
        ifstream file("parking_data.txt");
        if(!file) return;

        int f, s, type;
        string plate;
        time_t entry;

        while(file >> f >> s >> plate >> type >> entry) {
            for(auto &slot : slots) {
                if(slot.floor == f && slot.slotNumber == s) {
                    slot.vehicle =
                        new Vehicle(plate, (VehicleType)type);
                    slot.vehicle->entryTime = entry;
                    slot.isOccupied = true;
                }
            }
        }
        file.close();
    }
};

int main() {

    ParkingSystem system(2, 5); // 2 floors, 5 slots each

    int choice;

    while(true) {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Show Status\n";
        cout << "2. Park Vehicle\n";
        cout << "3. Remove Vehicle\n";
        cout << "4. Admin Panel\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: system.showStatus(); break;
            case 2: system.parkVehicle(); break;
            case 3: system.removeVehicle(); break;
            case 4: system.adminPanel(); break;
            case 5: return 0;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}
