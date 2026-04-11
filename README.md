# 🚗 Smart Parking Management System

An intelligent parking management system built using **C++** that efficiently manages vehicle parking, tracks occupancy, calculates revenue, and maintains persistent records.
Designed with a modular architecture, this project demonstrates strong **OOP principles, data structures, and system design**.

---

## 🚀 Features

* 🅿️ **Real-Time Parking Allocation**

  * Automatically assigns available slots across multiple floors

* 🔍 **Vehicle Search System**

  * Quickly locate a vehicle using plate number (O(1) lookup using hashmap)

* 💰 **Dynamic Billing System**

  * Calculates parking fees based on vehicle type and duration

* 📊 **Revenue Tracking**

  * Tracks total earnings with admin access

* 🧾 **Data Persistence**

  * Saves parking state to file
  * Reloads system state on restart

* 📁 **CSV Export**

  * Logs transactions for reporting

* 📝 **System Logging**

  * Records parking and removal events

* 🔐 **Secure Admin Access**

  * Password-protected admin panel (environment-based security)

---

## 🛠️ Tech Stack

* **Language:** C++ (C++17)
* **Concepts Used:**

  * Object-Oriented Programming (OOP)
  * STL (vector, unordered_map)
  * Smart Pointers (`shared_ptr`)
  * File Handling (fstream)
  * Time-based calculations (`chrono` / `ctime`)

---

## 📁 Project Structure

```id="2g8l1k"
smart-parking-management/
│
├── include/
│   ├── ParkingSystem.h
│   ├── ParkingSlot.h
│   └── Vehicle.h
│
├── src/
│   ├── ParkingSystem.cpp
│   ├── ParkingSlot.cpp
│   ├── Vehicle.cpp
│   └── main.cpp
│
├── data/
│   ├── parking_data.txt
│   ├── system_log.txt
│   └── revenue_report.csv
│
└── README.md
```

---

## ⚙️ How to Run

### 1. Compile

```bash id="k3p9a1"
g++ src/*.cpp -I include -std=c++17 -o parking
```

### 2. Run

```bash id="z9f2x8"
./parking
```

(On Windows: `.\parking`)

---

## 📊 How It Works

1. System initializes parking slots across floors
2. User selects an action:

   * Park vehicle
   * Remove vehicle
   * Search vehicle
   * View status
3. Vehicle is mapped to slot using hashmap
4. On exit:

   * Fee calculated based on duration
   * Revenue updated
   * Data saved to file

---

## 🔒 Security & Design Improvements

* No raw pointer misuse (safe memory handling)
* Input validation for vehicle type and plate number
* Encapsulation of internal data
* Environment-based admin password (secure configuration)

---

## 💡 Future Improvements

* 🌐 Web-based UI (convert to Flask/React)
* 📡 IoT integration (sensor-based slot detection)
* 🧠 AI-based parking prediction
* 📱 Mobile app for booking slots
* 🗺️ Real-time navigation to nearest available slot

---

## 📸 Sample Output

(Add console output screenshots here)

---

## 👨‍💻 Author

**Harshith H N**
IIT Bombay | Engineering Student

---

## ⭐ Contribution

Contributions are welcome! Feel free to fork and improve the system.

---
