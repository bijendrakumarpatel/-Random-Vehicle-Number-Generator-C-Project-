
---

# 🚗 Random Vehicle Number Generator (C++ + MySQL)

[![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

A **C++ console application** that generates **unique vehicle numbers** based on city and year. Supports **premium numbers**, tracks reservations, and stores all data in a **MySQL database** for persistence and management.

---

## ✨ Features

* Generate **random, unique vehicle numbers** per city and year.
* Support for **premium vehicle numbers** reserved for specific users.
* Stores **cities, users, vehicle numbers, and reservation history** in MySQL.
* Ensures **uniqueness** for all vehicle numbers.
* Modular, maintainable C++ code using **MySQL Connector/C++**.
* Console-based interface for **quick and easy interaction**.

---

## 🛠 Requirements

* **C++17** or later
* **MySQL Server**
* **MySQL Connector/C++** (`libmysqlcppconn-dev` on Ubuntu/Debian)

**Install dependencies on Ubuntu/Debian:**

```bash
sudo apt-get update
sudo apt-get install g++ cmake libmysqlcppconn-dev mysql-server
```

---

## ⚡ Setup

### 1. Start MySQL

```bash
sudo mysql
```

### 2. Create database and user

```sql
CREATE DATABASE vehicle_registry CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE USER 'vehicle_user'@'localhost' IDENTIFIED WITH mysql_native_password BY 'vehpass123';
GRANT ALL PRIVILEGES ON vehicle_registry.* TO 'vehicle_user'@'localhost';
FLUSH PRIVILEGES;
EXIT;
```

### 3. Import database schema

```bash
mysql -u vehicle_user -p < /path/to/schema.sql
# Enter password: vehpass123
```

### 4. Update database credentials in `main.cpp`

```cpp
driver->connect("tcp://127.0.0.1:3306", "vehicle_user", "vehpass123");
```

---

## 🏗 Compilation

```bash
cd /path/to/project/src
g++ main.cpp -o ../vehicle_app -lmysqlcppconn -std=c++17
```

---

## ▶ Running the Program

```bash
cd ..
./vehicle_app
```

**Steps:**

1. Enter **city code** (e.g., DEL, NYC).
2. Enter **year** (YYYY, e.g., 2025).
3. Indicate if it is **premium** (y/n).
4. If premium, enter **reserved by username**.

The program will:

* Generate a **unique vehicle number**.
* Save it to the **database**.
* Display all vehicle numbers for that city.

**Example:**

```bash
Enter city code (e.g., DEL): DEL
Enter year (YYYY): 2025
Is it premium? (y/n): y
Enter reserved by (username): admin
Generated Vehicle Number: DEL25A1Z9
```

---

## 📂 Database Schema Overview

* **users**: Stores registered users with premium flag.
* **cities**: Stores city codes and full city names.
* **vehicle\_numbers**: Stores generated vehicle numbers, ensuring uniqueness.
* **premium\_reservations**: Logs all premium vehicle reservations.

---

## 🚀 Future Enhancements

* **GUI or web frontend** for easier access.
* **User authentication** with secure password hashing.
* **REST API** for remote vehicle number generation.
* **Export options** to CSV, PDF, or Excel.
* **Bulk generation** for multiple cities and years.
* **Advanced reservation system** with expiration and notifications.
* **Analytics dashboard** showing most popular cities, years, or premium numbers.
* **Unit tests** and automated testing for reliability.

---

## 📜 License

This project is licensed under the **MIT License** – free to use, modify, and distribute.

---
