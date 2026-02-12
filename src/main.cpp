#include <iostream>
#include "ParkingSystem.h"

using namespace std;

int main() {
    ParkingSystem system(2, 5);
    int choice;

    while (true) {
        cout << "\n===== ELITE SMART PARKING SYSTEM =====\n";
        cout << "1. Show Status\n";
        cout << "2. Park Vehicle\n";
        cout << "3. Remove Vehicle\n";
        cout << "4. Admin Panel\n";
        cout << "5. Search Vehicle\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.showStatus(); break;
            case 2: system.parkVehicle(); break;
            case 3: system.removeVehicle(); break;
            case 4: system.adminPanel(); break;
            case 5: system.searchVehicle(); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}