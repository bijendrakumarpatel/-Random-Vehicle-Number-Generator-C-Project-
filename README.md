
````markdown
# 🚗 Random Vehicle Number Generator (C++ + MySQL)

A C++ console application to generate **unique vehicle numbers** based on city and year. Supports **premium numbers** with reservation tracking and stores all data in a **MySQL database**.

---

## ✨ Features

- Generate **random, unique vehicle numbers** per city and year.
- Supports **premium vehicle numbers** reserved by specific users.
- Stores **cities, users, vehicle numbers, and reservation history** in MySQL.
- Ensures **uniqueness** for all vehicle numbers.
- Modular C++ code with **MySQL Connector/C++**.
- Console interface for **easy interaction**.

---

## 🛠 Requirements

- C++17 or later
- MySQL Server
- MySQL Connector/C++ (`libmysqlcppconn-dev` on Ubuntu/Debian)

Install on Ubuntu:
```bash
sudo apt-get update
sudo apt-get install g++ cmake libmysqlcppconn-dev mysql-server
````



## ⚡ Setup

1. **Start MySQL and log in as root**

```bash
sudo mysql
```

2. **Create database and user**

```sql
CREATE DATABASE vehicle_registry CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

CREATE USER 'vehicle_user'@'localhost' IDENTIFIED WITH mysql_native_password BY 'vehpass123';
GRANT ALL PRIVILEGES ON vehicle_registry.* TO 'vehicle_user'@'localhost';
FLUSH PRIVILEGES;
EXIT;
```

3. **Import the database schema**

```bash
mysql -u vehicle_user -p < /path/to/schema.sql
# Enter password: vehpass123
```

4. **Update database credentials in `main.cpp`**

```cpp
driver->connect("tcp://127.0.0.1:3306", "vehicle_user", "vehpass123");
```

---

## 🏗 Compile

```bash
cd /path/to/project/src
g++ main.cpp -o ../vehicle_app -lmysqlcppconn -std=c++17
```

---

## ▶ Run the Program

```bash
cd ..
./vehicle_app
```

Follow the prompts:

1. Enter **city code** (e.g., DEL, NYC).
2. Enter **year** (YYYY, e.g., 2025).
3. Is it **premium?** (y/n)
4. If premium, enter **reserved by username**.

The program will:

* Generate a **unique vehicle number**.
* Save it to the **database**.
* List all vehicle numbers for that city.

---

## 📂 Database Schema Overview

* **users**: Stores users with premium flag.
* **cities**: Stores city codes and names.
* **vehicle\_numbers**: Stores generated vehicle numbers with uniqueness guarantee.
* **premium\_reservations**: Logs premium vehicle reservations.

---

## 🔗 Example Usage

```bash
Enter city code (e.g., DEL): DEL
Enter year (YYYY): 2025
Is it premium? (y/n): y
Enter reserved by (username): admin
Generated Vehicle Number: DEL25A1Z9
```

---

## 🚀 Future Improvements

* Add **GUI or web frontend**.
* User authentication and password hashing.
* Web API for remote vehicle number generation.
* Export vehicle numbers to CSV or PDF.

---

## 📜 License

MIT License – free to use and modify.

---
