#include "Animal.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
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
Animal::Animal() : animalID(""), commonName(""), scientificName(""),
                   habitat(""), conservationStatus("") {}

// Parameterized constructor
Animal::Animal(string id, string common, string scientific,
               string hab, string status)
    : animalID(id), commonName(common), scientificName(scientific),
      habitat(hab), conservationStatus(status) {}

// Virtual destructor - cleans up dynamically allocated photos
Animal::~Animal() {
    // Note: Photos are owned by Catalog; we just clear our references here
    photos.clear();
}

// --- Getter Implementations ---
string Animal::getAnimalID()           const { return animalID; }
string Animal::getCommonName()         const { return commonName; }
string Animal::getScientificName()     const { return scientificName; }
string Animal::getHabitat()            const { return habitat; }
string Animal::getConservationStatus() const { return conservationStatus; }
int    Animal::getPhotoCount()         const { return (int)photos.size(); }

// --- Setter Implementations ---
void Animal::setAnimalID(const string& id)          { animalID = id; }
void Animal::setCommonName(const string& name)       { commonName = name; }
void Animal::setScientificName(const string& name)   { scientificName = name; }
void Animal::setHabitat(const string& hab)           { habitat = hab; }
void Animal::setConservationStatus(const string& s)  { conservationStatus = s; }

// Add a photo to this animal's gallery (Composition)
void Animal::addPhoto(Photo* photo) {
    if (photo != nullptr) {
        photos.push_back(photo);
    }
}

// Remove a photo by ID
void Animal::removePhoto(const string& photoID) {
    photos.erase(
        remove_if(photos.begin(), photos.end(),
            [&](Photo* p) { return p->getPhotoID() == photoID; }),
        photos.end()
    );
}

vector<Photo*> Animal::getPhotos() const { return photos; }

// Display all linked photos
void Animal::displayPhotos() const {
    if (photos.empty()) {
        cout << YELLOW << "  No photos linked to this animal." << RESET << endl;
        return;
    }
    cout << CYAN << "\n  📸 Linked Photos (" << photos.size() << "):" << RESET << endl;
    for (auto* p : photos) {
        p->displayPhotoCompact();
    }
}

// Default displayDetails (virtual - can be overridden)
void Animal::displayDetails() const {
    cout << CYAN << "  ╔══════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "  ║ " << BOLD << GREEN << "🦁 ANIMAL RECORD" << RESET << CYAN << "                                       ║" << RESET << endl;
    cout << CYAN << "  ╠══════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "ID        : " << RESET << WHITE << left << setw(41) << animalID          << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "Common    : " << RESET << WHITE << left << setw(41) << commonName        << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "Scientific: " << RESET << YELLOW << left << setw(41) << scientificName    << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "Habitat   : " << RESET << WHITE << left << setw(41) << habitat           << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "Status    : " << RESET << WHITE << left << setw(41) << conservationStatus<< CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN << "Photos    : " << RESET << WHITE << left << setw(41) << photos.size()     << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ╚══════════════════════════════════════════════════════╝" << RESET << endl;
}