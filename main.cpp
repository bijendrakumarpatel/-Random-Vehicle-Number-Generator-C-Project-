#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <memory>
#include <stdexcept>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;

// Utility functions

string randomAlphaNum(int length) {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    string s;
    for (int i = 0; i < length; ++i)
        s += alphanum[dis(gen)];
    return s;
}

string yyFromYear(int year) {
    string y = to_string(year % 100);
    if (y.length() < 2) y = "0" + y;
    return y;
}

// Vehicle Repository
/
class VehicleRepo {
private:
    shared_ptr<sql::Connection> conn;

public:
    VehicleRepo(shared_ptr<sql::Connection> connection) : conn(connection) {}

    // Ensure city exists, returns city ID
    int ensureCity(const string& cityCode) {
        sql::PreparedStatement* sel = conn->prepareStatement(
            "SELECT id FROM cities WHERE code = ?"
        );
        sel->setString(1, cityCode);
        unique_ptr<sql::ResultSet> rs(sel->executeQuery());
        if (rs->next()) {
            int id = rs->getInt("id");
            delete sel;
            return id;
        }
        delete sel;

        // Insert if missing
        sql::PreparedStatement* ins = conn->prepareStatement(
            "INSERT INTO cities(code, name) VALUES (?, ?)"
        );
        ins->setString(1, cityCode);
        ins->setString(2, cityCode);
        ins->executeUpdate();
        delete ins;

        // Retrieve ID
        sel = conn->prepareStatement("SELECT id FROM cities WHERE code = ?");
        sel->setString(1, cityCode);
        rs.reset(sel->executeQuery());
        rs->next();
        int id = rs->getInt("id");
        delete sel;
        return id;
    }

    bool existsNumber(const string& number) {
        sql::PreparedStatement* ps = conn->prepareStatement(
            "SELECT id FROM vehicle_numbers WHERE number = ?"
        );
        ps->setString(1, number);
        unique_ptr<sql::ResultSet> rs(ps->executeQuery());
        bool exists = rs->next();
        delete ps;
        return exists;
    }

    void insertNumber(int cityId, int year, const string& number, bool premium, const string& reservedBy="") {
        sql::PreparedStatement* ps = conn->prepareStatement(
            "INSERT INTO vehicle_numbers(city_id, year_small, full_year, number, is_premium, reserved_by) "
            "VALUES (?, ?, ?, ?, ?, ?)"
        );
        ps->setInt(1, cityId);
        ps->setString(2, yyFromYear(year));
        ps->setInt(3, year);
        ps->setString(4, number);
        ps->setBoolean(5, premium);
        if (reservedBy.empty())
            ps->setNull(6, sql::DataType::VARCHAR);
        else
            ps->setString(6, reservedBy);
        ps->executeUpdate();
        delete ps;
    }

    void listByCity(const string& cityCode) {
        int cityId = ensureCity(cityCode);
        sql::PreparedStatement* ps = conn->prepareStatement(
            "SELECT vn.number, vn.full_year, vn.is_premium, vn.reserved_by, u.username "
            "FROM vehicle_numbers vn "
            "LEFT JOIN users u ON vn.reserved_by = u.username "
            "WHERE vn.city_id = ?"
        );
        ps->setInt(1, cityId);
        unique_ptr<sql::ResultSet> rs(ps->executeQuery());

        cout << "\nVehicle Numbers for city: " << cityCode << endl;
        cout << "---------------------------------------------" << endl;
        while (rs->next()) {
            cout << rs->getString("number")
                 << " | Year: " << rs->getInt("full_year")
                 << " | Premium: " << (rs->getBoolean("is_premium") ? "Yes" : "No")
                 << " | Reserved By: " << (rs->isNull("username") ? "-" : rs->getString("username"))
                 << endl;
        }
        delete ps;
    }
};

// Main Program

int main() {
    try {
        // Connect to MySQL
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        shared_ptr<sql::Connection> conn(
            driver->connect("tcp://127.0.0.1:3306", "vehicle_user", "vehpass123")
        );
        conn->setSchema("vehicle_registry");

        VehicleRepo repo(conn);

        string city;
        int year;
        char premiumInput;
        string reservedBy;

        cout << "Enter city code (e.g., DEL): ";
        cin >> city;
        cout << "Enter year (YYYY): ";
        cin >> year;
        cout << "Is it premium? (y/n): ";
        cin >> premiumInput;
        bool premium = (premiumInput == 'y' || premiumInput == 'Y');

        if (premium) {
            cout << "Enter reserved by (username): ";
            cin >> reservedBy;
        }

        int cityId = repo.ensureCity(city);

        // Generate unique number
        string number;
        do {
            number = city + yyFromYear(year) + randomAlphaNum(5); // total 9 chars
        } while (repo.existsNumber(number));

        // Insert into DB
        repo.insertNumber(cityId, year, number, premium, reservedBy);

        cout << "\n✅ Generated Vehicle Number: " << number << endl;

        // List all for city
        repo.listByCity(city);

    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
