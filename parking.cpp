#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

class Vehicle {
public:
    string number;
    string type;     // Bike / Car / Truck
    bool isVIP;
    time_t entryTime;

    Vehicle(string num = "", string t = "", bool vip = false) {
        number = num;
        type = t;
        isVIP = vip;
        entryTime = time(nullptr);
    }
};

class ParkingSlot {
public:
    bool occupied;
    Vehicle vehicle;

    ParkingSlot() {
        occupied = false;
    }
};

class SmartParking {
private:
    int floors;
    int slotsPerFloor;
    vector<vector<ParkingSlot>> parking;

    double totalRevenue = 0;
    int totalVehicles = 0;

    double getRate(string type) {
        if (type == "Bike") return 20;
        if (type == "Car") return 50;
        if (type == "Truck") return 80;
        return 50;
    }

public:
    SmartParking(int f, int s) {
        floors = f;
        slotsPerFloor = s;
        parking.resize(f, vector<ParkingSlot>(s));
    }

    void showStatus() {
        cout << "\n===== PARKING STATUS =====\n";
        for (int i = 0; i < floors; i++) {
            cout << "\nFloor " << i + 1 << ":\n";
            for (int j = 0; j < slotsPerFloor; j++) {
                cout << "Slot " << j + 1 << ": ";
                if (parking[i][j].occupied)
                    cout << "Occupied (" << parking[i][j].vehicle.number << ")";
                else
                    cout << "Available";
                cout << endl;
            }
        }
    }

    void parkVehicle(string number, string type, bool vip) {
        for (int i = 0; i < floors; i++) {
            for (int j = 0; j < slotsPerFloor; j++) {
                if (!parking[i][j].occupied) {
                    parking[i][j].occupied = true;
                    parking[i][j].vehicle = Vehicle(number, type, vip);
                    totalVehicles++;
                    cout << "\nVehicle parked at Floor "
                         << i + 1 << ", Slot " << j + 1 << endl;
                    return;
                }
            }
        }
        cout << "\nParking Full!\n";
    }

    void removeVehicle(string number) {
        for (int i = 0; i < floors; i++) {
            for (int j = 0; j < slotsPerFloor; j++) {
                if (parking[i][j].occupied &&
                    parking[i][j].vehicle.number == number) {

                    time_t exitTime = time(nullptr);
                    double hours = difftime(exitTime,
                                    parking[i][j].vehicle.entryTime) / 3600.0;
                    if (hours < 1) hours = 1;

                    double rate = getRate(parking[i][j].vehicle.type);
                    double fee = hours * rate;

                    if (parking[i][j].vehicle.isVIP)
                        fee *= 0.8;  // 20% discount

                    totalRevenue += fee;

                    cout << "\nVehicle removed.\n";
                    cout << "Type: " << parking[i][j].vehicle.type << endl;
                    cout << "Duration: " << hours << " hour(s)\n";
                    cout << "Fee: Rs. " << fee << endl;

                    parking[i][j] = ParkingSlot();
                    return;
                }
            }
        }
        cout << "\nVehicle not found!\n";
    }

    void adminPanel() {
        string password;
        cout << "\nEnter Admin Password: ";
        cin >> password;

        if (password != "admin123") {
            cout << "Access Denied!\n";
            return;
        }

        cout << "\n===== ADMIN DASHBOARD =====\n";
        cout << "Total Floors: " << floors << endl;
        cout << "Slots per Floor: " << slotsPerFloor << endl;
        cout << "Total Vehicles Served: " << totalVehicles << endl;
        cout << "Total Revenue: Rs. " << totalRevenue << endl;

        ofstream file("parking_report.txt");
        file << "SMART PARKING REPORT\n";
        file << "Total Vehicles: " << totalVehicles << endl;
        file << "Total Revenue: Rs. " << totalRevenue << endl;
        file.close();

        cout << "Report saved to parking_report.txt\n";
    }
};

int main() {
    int floors, slots;

    cout << "Enter number of floors: ";
    cin >> floors;

    cout << "Enter slots per floor: ";
    cin >> slots;

    SmartParking system(floors, slots);

    int choice;
    string number, type;
    int vipChoice;

    while (true) {
        cout << "\n===== SMART PARKING SYSTEM =====\n";
        cout << "1. Show Status\n";
        cout << "2. Park Vehicle\n";
        cout << "3. Remove Vehicle\n";
        cout << "4. Admin Panel\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.showStatus();
            break;
        case 2:
            cout << "Enter Vehicle Number: ";
            cin >> number;
            cout << "Enter Type (Bike/Car/Truck): ";
            cin >> type;
            cout << "Is VIP? (1=Yes,0=No): ";
            cin >> vipChoice;
            system.parkVehicle(number, type, vipChoice == 1);
            break;
        case 3:
            cout << "Enter Vehicle Number: ";
            cin >> number;
            system.removeVehicle(number);
            break;
        case 4:
            system.adminPanel();
            break;
        case 5:
            cout << "System Closing...\n";
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}
