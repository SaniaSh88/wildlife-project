#include "Catalog.h"
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

// ======================== CONSTRUCTOR / DESTRUCTOR ========================

Catalog::Catalog(const string& name) : catalogName(name) {}

// Destructor - properly frees all dynamically allocated memory
Catalog::~Catalog() {
    // Delete all Animal objects (polymorphic delete via virtual destructor)
    for (Animal* a : animals) delete a;
    // Delete all Habitat objects
    for (Habitat* h : habitats) delete h;
    // Delete all Photo objects
    for (Photo* p : photos) delete p;
    animals.clear();
    habitats.clear();
    photos.clear();
}

// ======================== ANIMAL MANAGEMENT ========================

void Catalog::addAnimal(Animal* animal) {
    if (animal) animals.push_back(animal);
}

bool Catalog::removeAnimal(const string& id) {
    for (auto it = animals.begin(); it != animals.end(); ++it) {
        if ((*it)->getAnimalID() == id) {
            delete *it;
            animals.erase(it);
            return true;
        }
    }
    return false;
}

// Search by exact ID
Animal* Catalog::searchAnimalByID(const string& id) const {
    for (Animal* a : animals) {
        if (a->getAnimalID() == id) return a;
    }
    return nullptr;
}

// Search by name (partial, case-insensitive)
vector<Animal*> Catalog::searchAnimalByName(const string& name) const {
    vector<Animal*> results;
    string lowerName = name;
    transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

    for (Animal* a : animals) {
        string lowerCommon = a->getCommonName();
        transform(lowerCommon.begin(), lowerCommon.end(), lowerCommon.begin(), ::tolower);
        if (lowerCommon.find(lowerName) != string::npos) {
            results.push_back(a);
        }
    }
    return results;
}

// Search by conservation status (case-insensitive)
vector<Animal*> Catalog::searchAnimalByStatus(const string& status) const {
    vector<Animal*> results;
    string lowerStatus = status;
    transform(lowerStatus.begin(), lowerStatus.end(), lowerStatus.begin(), ::tolower);

    for (Animal* a : animals) {
        string lowerS = a->getConservationStatus();
        transform(lowerS.begin(), lowerS.end(), lowerS.begin(), ::tolower);
        if (lowerS.find(lowerStatus) != string::npos) {
            results.push_back(a);
        }
    }
    return results;
}

vector<Animal*> Catalog::getAllAnimals() const { return animals; }

void Catalog::displayAllAnimals() const {
    if (animals.empty()) {
        cout << YELLOW << "  No species in the database.\n" << RESET;
        return;
    }
    cout << CYAN << "\n  ┌─────────────────────────────────────────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN <<   "  │ " << BOLD << GREEN << "  ID     " << YELLOW << "  Common Name           " << YELLOW << "  Scientific Name               " << "  Status               " << "Pop" << RESET << CYAN << "    │" << RESET << endl;
    cout << CYAN <<   "  ├─────────────────────────────────────────────────────────────────────────────────┤" << RESET << endl;
    for (Animal* a : animals) {
        Species* s = dynamic_cast<Species*>(a);  // Polymorphic cast
        if (s) s->displayCompact();
        else   a->displayDetails();
    }
    cout << CYAN << "  └─────────────────────────────────────────────────────────────────────────────────┘" << RESET << endl;
    cout << GREEN << "  Total: " << animals.size() << " species\n" << RESET;
}

// Display only Endangered or Critically Endangered species
void Catalog::displayEndangeredSpecies() const {
    vector<string> criticalStatuses = {"Endangered", "Critically Endangered", "Extinct"};
    bool found = false;

    cout << CYAN << "\n  ╔══════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "  ║ " << BOLD << RED << "🆘 ENDANGERED SPECIES ALERT" << RESET << CYAN << "                               ║" << RESET << endl;
    cout << CYAN << "  ╚══════════════════════════════════════════════════════════╝\n" << RESET << endl;

    for (Animal* a : animals) {
        string status = a->getConservationStatus();
        for (const string& cs : criticalStatuses) {
            if (status == cs) {
                a->displayDetails();
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << GREEN << "  ✅ No critically endangered species currently in the database.\n" << RESET;
    }
}

// ======================== HABITAT MANAGEMENT ========================

void Catalog::addHabitat(Habitat* habitat) {
    if (habitat) habitats.push_back(habitat);
}

bool Catalog::removeHabitat(const string& id) {
    for (auto it = habitats.begin(); it != habitats.end(); ++it) {
        if ((*it)->getHabitatID() == id) {
            delete *it;
            habitats.erase(it);
            return true;
        }
    }
    return false;
}

Habitat* Catalog::searchHabitatByID(const string& id) const {
    for (Habitat* h : habitats) {
        if (h->getHabitatID() == id) return h;
    }
    return nullptr;
}

vector<Habitat*> Catalog::searchHabitatByBiome(const string& biome) const {
    vector<Habitat*> results;
    string lowerBiome = biome;
    transform(lowerBiome.begin(), lowerBiome.end(), lowerBiome.begin(), ::tolower);

    for (Habitat* h : habitats) {
        string lowerH = h->getBiomeType();
        transform(lowerH.begin(), lowerH.end(), lowerH.begin(), ::tolower);
        if (lowerH.find(lowerBiome) != string::npos) {
            results.push_back(h);
        }
    }
    return results;
}

vector<Habitat*> Catalog::getAllHabitats() const { return habitats; }

void Catalog::displayAllHabitats() const {
    if (habitats.empty()) {
        cout << YELLOW << "  No habitats in the database.\n" << RESET;
        return;
    }
    cout << CYAN << "\n  ┌──────────────────────────────────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN <<   "  │ " << BOLD << GREEN << "  ID     " << YELLOW << "  Name                   " << BLUE << "  Biome         " << GREEN << "  Country           " << MAGENTA << "  Area" << RESET << CYAN << "           │" << RESET << endl;
    cout << CYAN <<   "  ├──────────────────────────────────────────────────────────────────────────┤" << RESET << endl;
    for (Habitat* h : habitats) {
        h->displayCompact();
    }
    cout << CYAN << "  └──────────────────────────────────────────────────────────────────────────┘" << RESET << endl;
    cout << GREEN << "  Total: " << habitats.size() << " habitats\n" << RESET;
}

// ======================== PHOTO MANAGEMENT ========================

void Catalog::addPhoto(Photo* photo) {
    if (photo) photos.push_back(photo);
}

bool Catalog::removePhoto(const string& id) {
    for (auto it = photos.begin(); it != photos.end(); ++it) {
        if ((*it)->getPhotoID() == id) {
            delete *it;
            photos.erase(it);
            return true;
        }
    }
    return false;
}

Photo* Catalog::searchPhotoByID(const string& id) const {
    for (Photo* p : photos) {
        if (p->getPhotoID() == id) return p;
    }
    return nullptr;
}

vector<Photo*> Catalog::searchPhotoByLocation(const string& location) const {
    vector<Photo*> results;
    string lowerLoc = location;
    transform(lowerLoc.begin(), lowerLoc.end(), lowerLoc.begin(), ::tolower);

    for (Photo* p : photos) {
        string lowerP = p->getLocation();
        transform(lowerP.begin(), lowerP.end(), lowerP.begin(), ::tolower);
        if (lowerP.find(lowerLoc) != string::npos) {
            results.push_back(p);
        }
    }
    return results;
}

vector<Photo*> Catalog::getAllPhotos() const { return photos; }

void Catalog::displayAllPhotos() const {
    if (photos.empty()) {
        cout << YELLOW << "  No photos in the gallery.\n" << RESET;
        return;
    }
    cout << CYAN << "\n  ┌──────────────────────────────────────────────────────────────────────────────┐" << RESET << endl;
    cout << CYAN <<   "  │ " << BOLD << YELLOW << "  ID     " << WHITE << "  Filename                " << GREEN << "  Location          " << MAGENTA << "  Date          " << BLUE << "  Res" << RESET << CYAN << "   │" << RESET << endl;
    cout << CYAN <<   "  ├──────────────────────────────────────────────────────────────────────────────┤" << RESET << endl;
    for (Photo* p : photos) {
        p->displayPhotoCompact();
    }
    cout << CYAN << "  └──────────────────────────────────────────────────────────────────────────────┘" << RESET << endl;
    cout << GREEN << "  Total: " << photos.size() << " photos\n" << RESET;
}

// Link a photo to an animal (by IDs)
bool Catalog::linkPhotoToAnimal(const string& photoID, const string& animalID) {
    Photo* photo   = searchPhotoByID(photoID);
    Animal* animal = searchAnimalByID(animalID);
    if (photo && animal) {
        animal->addPhoto(photo);
        return true;
    }
    return false;
}

// ======================== STATISTICS ========================

int Catalog::getTotalAnimals()  const { return (int)animals.size(); }
int Catalog::getTotalHabitats() const { return (int)habitats.size(); }
int Catalog::getTotalPhotos()   const { return (int)photos.size(); }

void Catalog::displayStatistics() const {
    // Count species by conservation status
    int stable = 0, nearThreatened = 0, vulnerable = 0,
        endangered = 0, critEndangered = 0, extinct = 0;

    for (Animal* a : animals) {
        string s = a->getConservationStatus();
        if      (s == "Stable")                stable++;
        else if (s == "Near Threatened")        nearThreatened++;
        else if (s == "Vulnerable")             vulnerable++;
        else if (s == "Endangered")             endangered++;
        else if (s == "Critically Endangered")  critEndangered++;
        else if (s == "Extinct")                extinct++;
    }

    // Count total linked photos
    int linkedPhotos = 0;
    for (Animal* a : animals) linkedPhotos += a->getPhotoCount();

    cout << CYAN  << "\n  ╔══════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN  << "  ║ " << BOLD << YELLOW << "📊 CATALOG STATISTICS" << RESET << CYAN << "                                          ║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << BOLD << WHITE << "  Catalog: " << RESET << YELLOW << left << setw(52) << catalogName << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << GREEN   << "  🦁 Total Species      : " << BOLD << WHITE  << left << setw(38) << animals.size()   << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << BLUE    << "  🌍 Total Habitats     : " << BOLD << WHITE  << left << setw(38) << habitats.size()  << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << MAGENTA << "  📸 Total Photos       : " << BOLD << WHITE  << left << setw(38) << photos.size()    << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << YELLOW  << "  🔗 Linked Photos      : " << BOLD << WHITE  << left << setw(38) << linkedPhotos     << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << BOLD << WHITE << "  Conservation Status Breakdown:" << RESET << string(31, ' ') << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << GREEN   << "    Stable              : " << BOLD << WHITE  << left << setw(38) << stable          << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << BLUE    << "    Near Threatened     : " << BOLD << WHITE  << left << setw(38) << nearThreatened  << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << YELLOW  << "    Vulnerable          : " << BOLD << WHITE  << left << setw(38) << vulnerable      << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << MAGENTA << "    Endangered          : " << BOLD << WHITE  << left << setw(38) << endangered      << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << RED     << "    Critically Endangered: " << BOLD << WHITE << left << setw(37) << critEndangered  << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << RED     << "    Extinct             : " << BOLD << WHITE  << left << setw(38) << extinct         << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ╚══════════════════════════════════════════════════════════════╝" << RESET << endl;
}

// ======================== CONSERVATION REPORT ========================

void Catalog::displayConservationReport() const {
    cout << CYAN  << "\n  ╔══════════════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN  << "  ║ " << BOLD << GREEN << "🌿 WILDLIFE CONSERVATION REPORT" << RESET << CYAN << "                              ║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << WHITE << "  Species tracked: " << BOLD << YELLOW << left << setw(44) << animals.size() << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << WHITE << "  Habitats mapped: " << BOLD << YELLOW << left << setw(44) << habitats.size() << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN  << "  ║ " << RESET << BOLD << WHITE << "  All Species Status:" << RESET << string(41, ' ') << CYAN << "║" << RESET << endl;
    cout << CYAN  << "  ╠══════════════════════════════════════════════════════════════╣" << RESET << endl;

    // Determine status color for each animal
    vector<pair<string,string>> statusColors = {
        {"Stable",                GREEN},
        {"Near Threatened",       BLUE},
        {"Vulnerable",            YELLOW},
        {"Endangered",            MAGENTA},
        {"Critically Endangered", RED},
        {"Extinct",               RED}
    };

    for (Animal* a : animals) {
        string statusCol = WHITE;
        for (auto& sc : statusColors) {
            if (a->getConservationStatus() == sc.first) { statusCol = sc.second; break; }
        }
        // Build the row string
        ostringstream row;
        row << "  " << left << setw(22) << a->getCommonName()
            << left << setw(18) << a->getConservationStatus();

        string icon = "  ";
        string st = a->getConservationStatus();
        if (st == "Endangered" || st == "Critically Endangered" || st == "Extinct") icon = "🆘";
        else if (st == "Vulnerable") icon = "⚠️ ";
        else icon = "✅";

        cout << CYAN << "  ║ " << RESET << icon << " " << statusCol << left << setw(60) << row.str() << CYAN << "║" << RESET << endl;
    }
    cout << CYAN  << "  ╚══════════════════════════════════════════════════════════════╝" << RESET << endl;
}

// ======================== SAMPLE DATA ========================

void Catalog::loadSampleData() {
    // --- Sample Species ---
    // POLYMORPHISM: Animal* pointers hold Species objects
    Animal* lion = new Species(
        "SP001", "African Lion", "Panthera leo",
        "Savanna", "Vulnerable",
        "Carnivore", "190 kg", "Viviparous", 23000
    );
    Animal* panda = new Species(
        "SP002", "Giant Panda", "Ailuropoda melanoleuca",
        "Temperate Forest", "Vulnerable",
        "Herbivore", "100 kg", "Viviparous", 1800
    );
    Animal* eagle = new Species(
        "SP003", "Bald Eagle", "Haliaeetus leucocephalus",
        "North America", "Stable",
        "Carnivore", "5 kg", "Oviparous", 70000
    );
    Animal* tiger = new Species(
        "SP004", "Bengal Tiger", "Panthera tigris tigris",
        "Tropical Forest", "Endangered",
        "Carnivore", "220 kg", "Viviparous", 2500
    );
    Animal* gorilla = new Species(
        "SP005", "Mountain Gorilla", "Gorilla beringei beringei",
        "Afromontane Forest", "Endangered",
        "Herbivore", "195 kg", "Viviparous", 1000
    );
    addAnimal(lion);
    addAnimal(panda);
    addAnimal(eagle);
    addAnimal(tiger);
    addAnimal(gorilla);

    // --- Sample Habitats ---
    Habitat* serengeti = new Habitat(
        "H001", "Serengeti National Park", "Savanna",
        "Tanzania", -6.369, 34.889, 30000
    );
    serengeti->addSpecies("African Lion");
    serengeti->addSpecies("African Elephant");
    serengeti->addSpecies("Wildebeest");

    Habitat* zhangjiajie = new Habitat(
        "H002", "Zhangjiajie Forest", "Temperate Forest",
        "China", 29.263, 110.476, 3000
    );
    zhangjiajie->addSpecies("Giant Panda");
    zhangjiajie->addSpecies("Golden Snub-nosed Monkey");

    Habitat* amazon = new Habitat(
        "H003", "Amazon Rainforest", "Tropical Rainforest",
        "Brazil", -3.465, -62.215, 5500000
    );
    amazon->addSpecies("Jaguar");
    amazon->addSpecies("Amazon River Dolphin");
    amazon->addSpecies("Green Anaconda");

    addHabitat(serengeti);
    addHabitat(zhangjiajie);
    addHabitat(amazon);

    // --- Sample Photos ---
    Photo* p1 = new Photo(
        "P001", "lion_pride.jpg", "Serengeti, Tanzania",
        "15/03/2024", "Sarah Johnson",
        "Majestic lion pride at golden sunset", "24 MP"
    );
    Photo* p2 = new Photo(
        "P002", "panda_eating.jpg", "Zhangjiajie, China",
        "20/04/2024", "Chen Wei",
        "Giant panda munching fresh bamboo", "18 MP"
    );
    Photo* p3 = new Photo(
        "P003", "eagle_soaring.jpg", "Alaska, USA",
        "05/07/2024", "Mike Thompson",
        "Bald eagle soaring over mountain peaks", "32 MP"
    );
    Photo* p4 = new Photo(
        "P004", "tiger_hunt.jpg", "Sundarbans, India",
        "12/09/2024", "Priya Sharma",
        "Bengal tiger stalking prey in tall grass", "20 MP"
    );
    addPhoto(p1);
    addPhoto(p2);
    addPhoto(p3);
    addPhoto(p4);

    // Link photos to animals
    linkPhotoToAnimal("P001", "SP001");
    linkPhotoToAnimal("P002", "SP002");
    linkPhotoToAnimal("P003", "SP003");
    linkPhotoToAnimal("P004", "SP004");
}

string Catalog::getCatalogName() const { return catalogName; }