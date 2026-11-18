AIR QUALITY MONITORING SYSTEM — C++ OOPS MINI PROJECT

FILES
- air_quality_monitor.cpp : complete C++ source code
- aqi_records.txt          : created automatically when records are saved

REQUIREMENTS
- C++11 or later compiler (g++, MinGW, or an IDE such as Code::Blocks)

COMPILE
    g++ -std=c++11 air_quality_monitor.cpp -o air_quality_monitor

RUN (Linux/macOS)
    ./air_quality_monitor

RUN (Windows)
    air_quality_monitor.exe

HOW TO USE
1. Run the program.
2. Choose "Add AQI reading" and enter a location and AQI value (0–500).
3. Display, search, or summarize saved readings.
4. Choose Save or Exit to write records to aqi_records.txt.

IMPORTANT SCOPE NOTE
This is an educational prototype. It accepts AQI values entered by the user and
classifies them using the category bands shown in the project report. It does not
connect to physical sensors, an official live AQI API, or a government database.
The displayed health advice is general educational guidance, not medical advice.

OOPS CONCEPTS
- Encapsulation: data members are protected/private and accessed through methods.
- Abstraction: Reading is an abstract base class with pure virtual methods.
- Inheritance: AQIReading derives from Reading.
- Polymorphism: category(), advice(), and display() are virtual functions.
- File handling: readings are saved to and loaded from a text file.
