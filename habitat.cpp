#include "Habitat.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"
#define WHITE   "\033[37m"

// Default constructor
Habitat::Habitat()
    : habitatID(""), name(""), biomeType(""), country(""),
      latitude(0.0), longitude(0.0), areaKmSquared(0.0) {}

// Parameterized constructor
Habitat::Habitat(string id, string n, string biome, string ctry,
                 double lat, double lon, double area)
    : habitatID(id), name(n), biomeType(biome), country(ctry),
      latitude(lat), longitude(lon), areaKmSquared(area) {}

Habitat::~Habitat() {}

// --- Getter Implementations ---
string Habitat::getHabitatID()     const { return habitatID; }
string Habitat::getName()          const { return name; }
string Habitat::getBiomeType()     const { return biomeType; }
string Habitat::getCountry()       const { return country; }
double Habitat::getLatitude()      const { return latitude; }
double Habitat::getLongitude()     const { return longitude; }
double Habitat::getAreaKmSquared() const { return areaKmSquared; }
vector<string> Habitat::getSpeciesNames() const { return speciesNames; }
int    Habitat::getSpeciesCount()  const { return (int)speciesNames.size(); }

// --- Setter Implementations ---
void Habitat::setHabitatID(const string& id)     { habitatID = id; }
void Habitat::setName(const string& n)            { name = n; }
void Habitat::setBiomeType(const string& biome)   { biomeType = biome; }
void Habitat::setCountry(const string& ctry)      { country = ctry; }
void Habitat::setLatitude(double lat)             { latitude = lat; }
void Habitat::setLongitude(double lon)            { longitude = lon; }
void Habitat::setAreaKmSquared(double area)       { areaKmSquared = area; }

// Add species name to this habitat
void Habitat::addSpecies(const string& speciesName) {
    // Avoid duplicates
    if (find(speciesNames.begin(), speciesNames.end(), speciesName) == speciesNames.end()) {
        speciesNames.push_back(speciesName);
    }
}

// Remove species name from this habitat
void Habitat::removeSpecies(const string& speciesName) {
    speciesNames.erase(
        remove(speciesNames.begin(), speciesNames.end(), speciesName),
        speciesNames.end()
    );
}

// Full habitat info display with box drawing and colors
void Habitat::displayHabitatInfo() const {
    cout << CYAN  << "  ╔══════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN  << "  ║ " << BOLD << BLUE << "🌍 HABITAT RECORD" << RESET << CYAN << "                                              ║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Habitat ID   : " << RESET << WHITE  << left << setw(47) << habitatID      << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Name         : " << RESET << BOLD << WHITE  << left << setw(47) << name           << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Biome Type   : " << RESET << YELLOW << left << setw(47) << biomeType      << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Country      : " << RESET << WHITE  << left << setw(47) << country        << CYAN << "║" << RESET << endl;

    // Format coordinates
    ostringstream coordStr;
    coordStr << fixed << setprecision(3) << latitude << ", " << longitude;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Coordinates  : " << RESET << MAGENTA << left << setw(47) << coordStr.str() << CYAN << "║" << RESET << endl;

    // Format area
    ostringstream areaStr;
    areaStr << fixed << setprecision(0) << areaKmSquared << " km²";
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Area         : " << RESET << WHITE  << left << setw(47) << areaStr.str()  << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET;
    cout << GREEN << "Species Count: " << RESET << BLUE   << left << setw(47) << speciesNames.size() << CYAN << "║" << RESET << endl;

    // List resident species
    if (!speciesNames.empty()) {
        cout << CYAN << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
        cout << CYAN << "  ║ " << RESET << GREEN << "Resident Species:" << RESET << string(44, ' ') << CYAN << "║" << RESET << endl;
        for (const auto& s : speciesNames) {
            string row = "  • " + s;
            cout << CYAN << "  ║ " << RESET << YELLOW << left << setw(62) << row << CYAN << "║" << RESET << endl;
        }
    }
    cout << CYAN  << "  ╚══════════════════════════════════════════════════════════════╝" << RESET << endl;
}

// Compact one-line display for lists
void Habitat::displayCompact() const {
    ostringstream areaStr;
    areaStr << fixed << setprecision(0) << areaKmSquared;

    cout << CYAN << "  [" << YELLOW << left << setw(6) << habitatID << CYAN << "] "
         << BOLD << WHITE << left << setw(25) << name
         << RESET << BLUE << left << setw(15) << biomeType
         << GREEN << left << setw(18) << country
         << MAGENTA << areaStr.str() << " km²"
         << RESET << endl;
}