#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

enum class VehicleType { BIKE = 1, CAR, TRUCK };

string vehicleTypeToString(VehicleType type) {
    switch(type) {
        case VehicleType::BIKE: return "Bike";
        case VehicleType::CAR: return "Car";
        case VehicleType::TRUCK: return "Truck";
    }
    return "Unknown";
}

class Vehicle {
public:
    string plate;
    VehicleType type;
    time_t entryTime;

    Vehicle(string p, VehicleType t)
        : plate(p), type(t), entryTime(time(nullptr)) {}
};

class ParkingSlot {
public:
    int floor;
    int number;
    bool occupied;
    shared_ptr<Vehicle> vehicle;

    ParkingSlot(int f, int n)
        : floor(f), number(n), occupied(false), vehicle(nullptr) {}
};

class ParkingSystem {
private:
    vector<ParkingSlot> slots;
    unordered_map<string, ParkingSlot*> vehicleIndex;
    double totalRevenue = 0;
    const string adminPassword = "elite123";

    double getRate(VehicleType type) {
        switch(type) {
            case VehicleType::BIKE: return 15;
            case VehicleType::CAR: return 30;
            case VehicleType::TRUCK: return 60;
        }
        return 0;
    }

    void logEvent(const string& message) {
        ofstream log("system_log.txt", ios::app);
        time_t now = time(nullptr);
        log << ctime(&now) << " - " << message << "\n";
        log.close();
    }

public:
    ParkingSystem(int floors, int perFloor) {
        for(int f=1; f<=floors; f++)
            for(int s=1; s<=perFloor; s++)
                slots.emplace_back(f, s);

        loadData();
    }

    void showStatus() {
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

    void parkVehicle() {
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

    void removeVehicle() {
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

    void adminPanel() {
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

    void exportRevenueCSV(string plate, double fee) {
        ofstream csv("revenue_report.csv", ios::app);
        time_t now = time(nullptr);
        csv << plate << ","
            << fee << ","
            << ctime(&now);
        csv.close();
    }

    void saveData() {
        ofstream file("parking_data.txt");
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
        file.close();
    }

    void loadData() {
        ifstream file("parking_data.txt");
        if(!file) return;

        string plate;
        int f, s, type;
        time_t entry;
        string tag;

        while(file >> f) {
            if(f == 0) break;
            file >> s >> plate >> type >> entry;

            for(auto &slot : slots) {
                if(slot.floor == f && slot.number == s) {
                    slot.vehicle =
                        make_shared<Vehicle>(
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
        file.close();
    }
};

int main() {

    ParkingSystem system(3, 5); // 3 floors, 5 slots each

    int choice;

    while(true) {
        cout << "\n===== ELITE SMART PARKING SYSTEM =====\n";
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
