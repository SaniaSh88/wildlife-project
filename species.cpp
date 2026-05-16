#include "Species.h"
#include <iostream>
#include <iomanip>
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

// Default constructor - calls parent (Animal) default constructor via initializer list
Species::Species()
    : Animal(), diet(""), averageWeight(""), reproductionType(""), populationEstimate(0) {}

// Parameterized constructor - calls Animal constructor (INHERITANCE)
Species::Species(string id, string common, string scientific,
                 string habitat, string status,
                 string d, string weight, string reproType, int population)
    : Animal(id, common, scientific, habitat, status),  // Call parent constructor
      diet(d), averageWeight(weight), reproductionType(reproType),
      populationEstimate(population) {}

Species::~Species() {}

// --- Getter Implementations ---
string Species::getDiet()              const { return diet; }
string Species::getAverageWeight()     const { return averageWeight; }
string Species::getReproductionType()  const { return reproductionType; }
int    Species::getPopulationEstimate()const { return populationEstimate; }

// --- Setter Implementations ---
void Species::setDiet(const string& d)           { diet = d; }
void Species::setAverageWeight(const string& w)  { averageWeight = w; }
void Species::setReproductionType(const string& t){ reproductionType = t; }
void Species::setPopulationEstimate(int p)       { populationEstimate = p; }

// Helper to get ANSI color for conservation status
string Species::getStatusColor() const {
    if (conservationStatus == "Extinct")              return RED;
    if (conservationStatus == "Critically Endangered") return RED;
    if (conservationStatus == "Endangered")            return MAGENTA;
    if (conservationStatus == "Vulnerable")            return YELLOW;
    if (conservationStatus == "Near Threatened")       return BLUE;
    if (conservationStatus == "Stable")                return GREEN;
    return WHITE;
}

// OVERRIDE of pure virtual getInfo() - POLYMORPHISM in action
// This method MUST be implemented to make Species a concrete (non-abstract) class
string Species::getInfo() const {
    ostringstream oss;
    oss << "[" << animalID << "] "
        << commonName << " (" << scientificName << ")"
        << " | Status: " << conservationStatus
        << " | Pop: " << populationEstimate
        << " | Diet: " << diet;
    return oss.str();
}

// OVERRIDE of virtual displayDetails() - POLYMORPHISM
// This overrides Animal::displayDetails() with species-specific information
void Species::displayDetails() const {
    string statusColor = getStatusColor();

    cout << CYAN << "  ╔══════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "  ║ " << BOLD << GREEN << "🦁 SPECIES RECORD" << RESET << CYAN << "                                              ║" << RESET << endl;
    cout << CYAN << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN << "  ║ " << RESET;
    cout << GREEN  << "Species ID   : " << RESET << WHITE  << left << setw(47) << animalID          << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Common Name  : " << RESET << BOLD   << WHITE << left << setw(47) << commonName        << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Scientific   : " << RESET << YELLOW << left << setw(47) << scientificName    << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Habitat      : " << RESET << BLUE   << left << setw(47) << habitat           << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Diet         : " << RESET << WHITE  << left << setw(47) << diet              << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Avg Weight   : " << RESET << WHITE  << left << setw(47) << averageWeight     << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Reproduction : " << RESET << WHITE  << left << setw(47) << reproductionType  << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;

    // Color-code population estimate based on urgency
    string popStr = to_string(populationEstimate) + " individuals";
    string popColor = (populationEstimate < 5000) ? RED :
                      (populationEstimate < 20000) ? YELLOW : GREEN;
    cout << GREEN  << "Population   : " << RESET << popColor << left << setw(47) << popStr << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;

    // Color-coded conservation status
    string statusStr = conservationStatus;
    cout << GREEN  << "Cons. Status : " << RESET << statusColor << BOLD << left << setw(47) << statusStr << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ║ " << RESET;
    cout << GREEN  << "Photos Linked: " << RESET << MAGENTA << left << setw(47) << photos.size()     << CYAN << "║" << RESET << endl;
    cout << CYAN   << "  ╚══════════════════════════════════════════════════════════════╝" << RESET << endl;
}

// Compact one-line display for use in lists
void Species::displayCompact() const {
    string statusColor = getStatusColor();
    cout << CYAN << "  [" << YELLOW << left << setw(6) << animalID << CYAN << "] "
         << BOLD << WHITE << left << setw(22) << commonName
         << RESET << YELLOW << left << setw(28) << scientificName
         << statusColor << left << setw(22) << conservationStatus
         << GREEN << "Pop: " << populationEstimate
         << RESET << endl;
}