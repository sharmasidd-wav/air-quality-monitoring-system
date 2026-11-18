#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
using namespace std;

// Base class: demonstrates abstraction and inheritance.
class Reading {
protected:
    string location;
    int aqi;
public:
    Reading(const string& place = "", int value = 0)
        : location(place), aqi(value) {}

    virtual string category() const = 0;
    virtual string advice() const = 0;

    string getLocation() const { return location; }
    int getAQI() const { return aqi; }

    virtual void display() const {
        cout << left << setw(20) << location
             << setw(8) << aqi
             << setw(22) << category()
             << advice() << '\n';
    }

    virtual ~Reading() = default;
};

// Derived class: AQI-specific reading and classification.
class AQIReading : public Reading {
public:
    AQIReading(const string& place, int value) : Reading(place, value) {}

    string category() const override {
        if (aqi <= 50) return "Good";
        if (aqi <= 100) return "Satisfactory";
        if (aqi <= 200) return "Moderate";
        if (aqi <= 300) return "Poor";
        if (aqi <= 400) return "Very Poor";
        return "Severe";
    }

    string advice() const override {
        if (aqi <= 50) return "Air quality is satisfactory.";
        if (aqi <= 100) return "Sensitive people should take care.";
        if (aqi <= 200) return "People with breathing issues should limit prolonged outdoor exertion.";
        if (aqi <= 300) return "Avoid prolonged outdoor exertion; sensitive groups should stay indoors.";
        if (aqi <= 400) return "Avoid outdoor physical activity.";
        return "Stay indoors; avoid outdoor exposure.";
    }
};

// Manages readings, reports and persistent storage.
class AirQualityMonitor {
private:
    vector<AQIReading> records;
    const string fileName = "aqi_records.txt";

public:
    void addReading() {
        string place;
        int value;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter location name: ";
        getline(cin, place);

        if (place.empty()) {
            cout << "Location cannot be empty.\n";
            return;
        }

        cout << "Enter AQI value (0-500): ";
        if (!(cin >> value) || value < 0 || value > 500) {
            cout << "Invalid AQI. Please enter a value from 0 to 500.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        records.emplace_back(place, value);
        cout << "Reading added successfully.\n";
    }

    void showAll() const {
        if (records.empty()) {
            cout << "No readings available. Add a reading first.\n";
            return;
        }

        cout << "\n" << left << setw(20) << "Location"
             << setw(8) << "AQI" << setw(22) << "Category"
             << "Health advice\n";
        cout << string(90, '-') << '\n';

        for (const auto& record : records)
            record.display();
    }

    void searchLocation() const {
        string place;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter location to search: ";
        getline(cin, place);

        bool found = false;
        for (const auto& record : records) {
            if (record.getLocation() == place) {
                record.display();
                found = true;
            }
        }
        if (!found) cout << "No record found for " << place << ".\n";
    }

    void showSummary() const {
        if (records.empty()) {
            cout << "No data available for summary.\n";
            return;
        }

        int total = 0;
        auto worst = records.begin();
        for (auto it = records.begin(); it != records.end(); ++it) {
            total += it->getAQI();
            if (it->getAQI() > worst->getAQI()) worst = it;
        }

        cout << fixed << setprecision(2);
        cout << "Number of readings: " << records.size() << '\n';
        cout << "Average AQI: " << static_cast<double>(total) / records.size() << '\n';
        cout << "Highest AQI: " << worst->getAQI()
             << " at " << worst->getLocation() << '\n';
    }

    void saveToFile() const {
        ofstream file(fileName);
        if (!file) {
            cout << "Unable to open file for saving.\n";
            return;
        }

        for (const auto& record : records)
            file << record.getLocation() << '\n' << record.getAQI() << '\n';

        cout << "Records saved to " << fileName << ".\n";
    }

    void loadFromFile() {
        ifstream file(fileName);
        if (!file) {
            cout << "No previous data file found. Starting with an empty list.\n";
            return;
        }

        records.clear();
        string place;
        int value;
        while (getline(file, place)) {
            if (!(file >> value)) break;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0 && value <= 500)
                records.emplace_back(place, value);
        }
        cout << records.size() << " record(s) loaded.\n";
    }
};

int main() {
    AirQualityMonitor monitor;
    monitor.loadFromFile();

    int choice;
    do {
        cout << "\n========== AIR QUALITY MONITORING SYSTEM ==========\n"
             << "1. Add AQI reading\n"
             << "2. Display all readings\n"
             << "3. Search readings by location\n"
             << "4. Show summary\n"
             << "5. Save records\n"
             << "0. Exit\n"
             << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a menu number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: monitor.addReading(); break;
            case 2: monitor.showAll(); break;
            case 3: monitor.searchLocation(); break;
            case 4: monitor.showSummary(); break;
            case 5: monitor.saveToFile(); break;
            case 0:
                monitor.saveToFile();
                cout << "Thank you for using the system. Goodbye!\n";
                break;
            default: cout << "Please choose a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
