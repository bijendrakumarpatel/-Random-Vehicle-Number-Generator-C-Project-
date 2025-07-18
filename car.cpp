#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <cmath>
#include <set>
#include <fstream>

using namespace std;

/*
===============================================================================
Project Title: Random Vehicle Number Generator (Enhanced Version)
Author: Bijendra Kumar Patel
Date: July 2025
===============================================================================
New Features & Updates:

1. New Function: saveToFile()
   → Saves all generated vehicle numbers to a file named "vehicle_numbers.txt"
   → Ensures data is not lost after the program exits.

2. New Function: loadFromFile()
   → Loads previously saved vehicle numbers from "vehicle_numbers.txt" on startup
   → Maintains continuity across multiple program runs.

3. Enhanced Menu Options:
   🆕 Option 3: Show all generated vehicle numbers
       - Lists all numbers saved in the file or created in the current session.
   
   🆕 Option 4: Count total vehicle numbers
       - Displays the number of unique vehicle numbers generated so far.
   
   🆕 Option 5: Clear all saved numbers
       - Deletes all entries from memory and clears the file permanently.

4. Persistent Storage:
   → The program now uses file I/O to store and retrieve data beyond a single session.

5. Clean Code Improvements:
   → Removed std:: by using "using namespace std"
   → Improved input validation and program structure for clarity and reusability.

===============================================================================
*/

// Convert a string to uppercase
string toUpperCase(const string& input) {
    string result = input;
    for (char& c : result) {
        c = toupper(c);
    }
    return result;
}

// Generate a random number in a range
int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Validate city
bool isValidCity(const string& city) {
    return city.length() >= 3;
}

// Validate year
bool isValidYear(int year) {
    int currentYear = 2026;
    return year >= 1900 && year <= currentYear;
}

// Get city input
string getCityInput() {
    string city;
    while (true) {
        cout << "Enter the city name (minimum 3 characters): ";
        getline(cin, city);
        if (isValidCity(city)) return city;
        cout << "Invalid city name. Try again.\n";
    }
}

// Get year input
int getYearInput() {
    int year;
    while (true) {
        cout << "Enter the year (1900 - 2026): ";
        cin >> year;
        if (isValidYear(year)) return year;
        cout << "Invalid year. Try again.\n";
    }
}

// Generate vehicle number
string generateVehicleNumber(const string& city, int year) {
    string vehicleNumber;
    vehicleNumber += toUpperCase(city.substr(0, 3));
    vehicleNumber += to_string(year % 100);

    int remainingLength = 9 - vehicleNumber.length();
    int randomID = randomNumber(1, static_cast<int>(pow(10, remainingLength)) - 1);
    vehicleNumber += to_string(randomID);

    return vehicleNumber;
}

// Check if number exists
bool isNumberExists(const set<string>& numbers, const string& number) {
    return numbers.find(number) != numbers.end();
}

// Save numbers to file
void saveToFile(const set<string>& numbers, const string& filename = "vehicle_numbers.txt") {
    ofstream out(filename);
    for (const string& num : numbers) {
        out << num << endl;
    }
    out.close();
}

// Load numbers from file
set<string> loadFromFile(const string& filename = "vehicle_numbers.txt") {
    set<string> numbers;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        if (!line.empty()) numbers.insert(line);
    }
    in.close();
    return numbers;
}

// Display menu
void displayMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Generate a new vehicle number\n";
    cout << "2. Check if a vehicle number exists\n";
    cout << "3. Show all generated vehicle numbers\n";
    cout << "4. Count total vehicle numbers\n";
    cout << "5. Clear all saved numbers\n";
    cout << "6. Exit\n";
    cout << "==========================\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    set<string> vehicleNumbers = loadFromFile();

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string city = getCityInput();
            int year = getYearInput();
            string vehicleNumber = generateVehicleNumber(city, year);

            vehicleNumbers.insert(vehicleNumber);
            saveToFile(vehicleNumbers);
            cout << "Generated Vehicle Number: " << vehicleNumber << endl;

        } else if (choice == 2) {
            string numberToCheck;
            cout << "Enter vehicle number to check: ";
            getline(cin, numberToCheck);

            if (isNumberExists(vehicleNumbers, numberToCheck))
                cout << numberToCheck << " exists.\n";
            else
                cout << numberToCheck << " does not exist.\n";

        } else if (choice == 3) {
            cout << "\nAll Generated Vehicle Numbers:\n";
            for (const string& num : vehicleNumbers)
                cout << "- " << num << endl;

        } else if (choice == 4) {
            cout << "Total vehicle numbers generated: " << vehicleNumbers.size() << endl;

        } else if (choice == 5) {
            vehicleNumbers.clear();
            saveToFile(vehicleNumbers);
            cout << "All saved numbers cleared.\n";

        } else if (choice == 6) {
            cout << "Exiting. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
