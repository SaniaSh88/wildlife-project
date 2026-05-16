// ============================================================
// WILDLIFE PHOTOGRAPHY CATALOG & CONSERVATION AWARENESS PLATFORM
// C++ OOP Semester Project
//
// OOP Concepts Demonstrated:
//   1. ENCAPSULATION  - Private data + public getters/setters
//   2. INHERITANCE    - Species extends Animal (abstract class)
//   3. POLYMORPHISM   - Virtual/override methods, Animal* holding Species
//   4. ABSTRACTION    - Abstract base class Animal with pure virtual getInfo()
//   5. COMPOSITION    - Catalog has Animals; Animals have Photos
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Catalog.h"
#include "Species.h"
#include "Habitat.h"
#include "Photo.h"
using namespace std;

// ---- ANSI Color Codes ----
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"
#define BLUE    "\033[34m"
#define BOLD    "\033[1m"
#define WHITE   "\033[37m"

// ======================== UTILITY FUNCTIONS ========================

void clearScreen() {
    cout << "\033[2J\033[H";  // ANSI clear screen
}

void pauseScreen() {
    cout << "\n" << CYAN << "  Press Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printBanner() {
    cout << CYAN << "\n";
    cout << "  ╔══════════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║                                                                      ║\n";
    cout << "  ║  " << BOLD << GREEN << "🌍 WILDLIFE PHOTOGRAPHY CATALOG" << RESET << CYAN << "                                    ║\n";
    cout << "  ║  " << BOLD << YELLOW << "   & CONSERVATION AWARENESS PLATFORM" << RESET << CYAN << "                               ║\n";
    cout << "  ║                                                                      ║\n";
    cout << "  ║  " << MAGENTA << "Protecting Species · Preserving Habitats · Photography Art" << CYAN << "       ║\n";
    cout << "  ║                                                                      ║\n";
    cout << "  ╚══════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET << endl;
}

void printSectionHeader(const string& title, const string& icon) {
    cout << CYAN << "\n  ╔══════════════════════════════════════════════════════════════╗\n";
    cout << "  ║  " << BOLD << YELLOW << icon << " " << title << RESET << CYAN;
    int padding = 57 - (int)title.size() - (int)icon.size();
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "║\n";
    cout << "  ╚══════════════════════════════════════════════════════════════╝\n" << RESET << endl;
}

int getMenuChoice(int min, int max) {
    int choice = -1;
    while (true) {
        cout << YELLOW << "  Enter your choice [" << min << "-" << max << "]: " << RESET;
        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "  ❌ Invalid input. Please try again.\n" << RESET;
    }
}

string getInput(const string& prompt) {
    cout << CYAN << "  " << prompt << ": " << RESET;
    string input;
    getline(cin, input);
    return input;
}

// ======================== MENU DISPLAY FUNCTIONS ========================

void displayMainMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << YELLOW << "         🌿 MAIN MENU" << RESET << CYAN << "                    │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. 🦁 Wildlife Database" << RESET << CYAN << "                │\n";
    cout << "  │ " << BLUE   << "  2. 📸 Photography Gallery" << RESET << CYAN << "              │\n";
    cout << "  │ " << MAGENTA<< "  3. 🌿 Conservation Center" << RESET << CYAN << "             │\n";
    cout << "  │ " << YELLOW << "  4. 📊 Statistics" << RESET << CYAN << "                       │\n";
    cout << "  │ " << RED    << "  5. 🚪 Exit" << RESET << CYAN << "                             │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

void displayWildlifeMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << GREEN << "       🦁 WILDLIFE DATABASE" << RESET << CYAN << "              │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. ➕ Add New Species" << RESET << CYAN << "                  │\n";
    cout << "  │ " << YELLOW << "  2. 📋 View All Species" << RESET << CYAN << "                 │\n";
    cout << "  │ " << CYAN   << "  3. 🔍 Search Species" << RESET << CYAN << "                   │\n";
    cout << "  │ " << BLUE   << "  4. 🗑️  Remove Species" << RESET << CYAN << "                  │\n";
    cout << "  │ " << MAGENTA<< "  5. 🌍 Manage Habitats" << RESET << CYAN << "                  │\n";
    cout << "  │ " << RED    << "  6. ← Back to Main Menu" << RESET << CYAN << "                │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

void displaySearchSpeciesMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << CYAN << "       🔍 SEARCH SPECIES" << RESET << CYAN << "                 │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. 🆔 Search by ID" << RESET << CYAN << "                    │\n";
    cout << "  │ " << YELLOW << "  2. 🔤 Search by Name" << RESET << CYAN << "                  │\n";
    cout << "  │ " << RED    << "  3. 🚨 Search by Conservation Status" << RESET << CYAN << "   │\n";
    cout << "  │ " << MAGENTA<< "  4. ← Back" << RESET << CYAN << "                             │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

void displayHabitatMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << BLUE << "       🌍 HABITAT MANAGEMENT" << RESET << CYAN << "            │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. ➕ Add New Habitat" << RESET << CYAN << "                  │\n";
    cout << "  │ " << YELLOW << "  2. 📋 View All Habitats" << RESET << CYAN << "                │\n";
    cout << "  │ " << CYAN   << "  3. 🔍 Search by ID" << RESET << CYAN << "                    │\n";
    cout << "  │ " << MAGENTA<< "  4. 🌱 Search by Biome" << RESET << CYAN << "                  │\n";
    cout << "  │ " << BLUE   << "  5. 🗑️  Remove Habitat" << RESET << CYAN << "                  │\n";
    cout << "  │ " << RED    << "  6. ← Back" << RESET << CYAN << "                             │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

void displayPhotographyMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << MAGENTA << "      📸 PHOTOGRAPHY GALLERY" << RESET << CYAN << "            │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. ➕ Add New Photo" << RESET << CYAN << "                   │\n";
    cout << "  │ " << YELLOW << "  2. 📋 View All Photos" << RESET << CYAN << "                  │\n";
    cout << "  │ " << CYAN   << "  3. 🔍 Search by ID" << RESET << CYAN << "                    │\n";
    cout << "  │ " << MAGENTA<< "  4. 📍 Search by Location" << RESET << CYAN << "               │\n";
    cout << "  │ " << BLUE   << "  5. 🔗 Link Photo to Species" << RESET << CYAN << "            │\n";
    cout << "  │ " << WHITE  << "  6. 🗑️  Remove Photo" << RESET << CYAN << "                   │\n";
    cout << "  │ " << RED    << "  7. ← Back to Main Menu" << RESET << CYAN << "                │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

void displayConservationMenu() {
    cout << CYAN << "\n  ┌─────────────────────────────────────────┐\n";
    cout << "  │ " << BOLD << GREEN << "     🌿 CONSERVATION CENTER" << RESET << CYAN << "              │\n";
    cout << "  ├─────────────────────────────────────────┤\n";
    cout << "  │ " << GREEN  << "  1. 📄 Full Conservation Report" << RESET << CYAN << "         │\n";
    cout << "  │ " << RED    << "  2. 🆘 View Endangered Species" << RESET << CYAN << "          │\n";
    cout << "  │ " << YELLOW << "  3. 🔍 Search by Status" << RESET << CYAN << "                 │\n";
    cout << "  │ " << MAGENTA<< "  4. ← Back to Main Menu" << RESET << CYAN << "                │\n";
    cout << "  └─────────────────────────────────────────┘\n" << RESET << endl;
}

// ======================== SPECIES HANDLERS ========================

void handleAddSpecies(Catalog& catalog) {
    printSectionHeader("ADD NEW SPECIES", "🦁");

    string id      = getInput("Species ID (e.g. SP006)");
    string common  = getInput("Common Name");
    string sci     = getInput("Scientific Name");
    string habitat = getInput("Habitat");
    cout << CYAN << "  Conservation Status options: Stable / Near Threatened / Vulnerable / Endangered / Critically Endangered / Extinct\n" << RESET;
    string status  = getInput("Conservation Status");
    string diet    = getInput("Diet (e.g. Carnivore)");
    string weight  = getInput("Average Weight (e.g. 150 kg)");
    string repro   = getInput("Reproduction Type (e.g. Viviparous)");
    string popStr  = getInput("Population Estimate (number)");

    int pop = 0;
    try { pop = stoi(popStr); } catch (...) { pop = 0; }

    // POLYMORPHISM: create Species* stored as Animal*
    Animal* newSpecies = new Species(id, common, sci, habitat, status, diet, weight, repro, pop);
    catalog.addAnimal(newSpecies);

    cout << GREEN << "\n  ✅ Species '" << common << "' added successfully!\n" << RESET;
}

void handleSearchSpecies(Catalog& catalog) {
    while (true) {
        displaySearchSpeciesMenu();
        int choice = getMenuChoice(1, 4);

        if (choice == 4) break;

        if (choice == 1) {
            // Search by ID
            string id = getInput("Enter Species ID");
            Animal* a = catalog.searchAnimalByID(id);
            if (a) {
                cout << "\n";
                a->displayDetails();  // POLYMORPHISM: calls Species::displayDetails()
                a->displayPhotos();
            } else {
                cout << RED << "  ❌ Species with ID '" << id << "' not found.\n" << RESET;
            }
        }
        else if (choice == 2) {
            // Search by Name
            string name = getInput("Enter Species Name (partial ok)");
            auto results = catalog.searchAnimalByName(name);
            if (results.empty()) {
                cout << RED << "  ❌ No species found matching '" << name << "'.\n" << RESET;
            } else {
                cout << GREEN << "  Found " << results.size() << " result(s):\n\n" << RESET;
                for (Animal* a : results) {
                    a->displayDetails();  // POLYMORPHISM
                }
            }
        }
        else if (choice == 3) {
            // Search by Conservation Status
            string status = getInput("Enter Conservation Status");
            auto results  = catalog.searchAnimalByStatus(status);
            if (results.empty()) {
                cout << RED << "  ❌ No species found with status '" << status << "'.\n" << RESET;
            } else {
                cout << GREEN << "  Found " << results.size() << " result(s):\n\n" << RESET;
                for (Animal* a : results) {
                    a->displayDetails();
                }
            }
        }
        pauseScreen();
    }
}

void handleRemoveSpecies(Catalog& catalog) {
    string id = getInput("Enter Species ID to remove");
    Animal* a = catalog.searchAnimalByID(id);
    if (!a) {
        cout << RED << "  ❌ Species not found.\n" << RESET;
        return;
    }
    cout << YELLOW << "  Remove '" << a->getCommonName() << "'? (y/n): " << RESET;
    char confirm;
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (confirm == 'y' || confirm == 'Y') {
        catalog.removeAnimal(id);
        cout << GREEN << "  ✅ Species removed successfully.\n" << RESET;
    } else {
        cout << YELLOW << "  Removal cancelled.\n" << RESET;
    }
}

// ======================== HABITAT HANDLERS ========================

void handleHabitatMenu(Catalog& catalog) {
    while (true) {
        displayHabitatMenu();
        int choice = getMenuChoice(1, 6);

        if (choice == 6) break;

        if (choice == 1) {
            // Add Habitat
            printSectionHeader("ADD NEW HABITAT", "🌍");
            string id      = getInput("Habitat ID (e.g. H004)");
            string name    = getInput("Habitat Name");
            string biome   = getInput("Biome Type");
            string country = getInput("Country");
            string latStr  = getInput("Latitude (decimal degrees)");
            string lonStr  = getInput("Longitude (decimal degrees)");
            string areaStr = getInput("Area (km²)");

            double lat = 0, lon = 0, area = 0;
            try { lat = stod(latStr); lon = stod(lonStr); area = stod(areaStr); } catch (...) {}

            Habitat* h = new Habitat(id, name, biome, country, lat, lon, area);

            string speciesInput;
            cout << CYAN << "  Add species to this habitat? (enter name, empty to stop):\n" << RESET;
            while (true) {
                speciesInput = getInput("  Species name (or Enter to finish)");
                if (speciesInput.empty()) break;
                h->addSpecies(speciesInput);
            }

            catalog.addHabitat(h);
            cout << GREEN << "\n  ✅ Habitat '" << name << "' added successfully!\n" << RESET;
        }
        else if (choice == 2) {
            printSectionHeader("ALL HABITATS", "🌍");
            catalog.displayAllHabitats();
        }
        else if (choice == 3) {
            string id = getInput("Enter Habitat ID");
            Habitat* h = catalog.searchHabitatByID(id);
            if (h) h->displayHabitatInfo();
            else cout << RED << "  ❌ Habitat not found.\n" << RESET;
        }
        else if (choice == 4) {
            string biome = getInput("Enter Biome Type");
            auto results = catalog.searchHabitatByBiome(biome);
            if (results.empty()) cout << RED << "  ❌ No habitats found for biome '" << biome << "'.\n" << RESET;
            else for (Habitat* h : results) h->displayHabitatInfo();
        }
        else if (choice == 5) {
            string id = getInput("Enter Habitat ID to remove");
            Habitat* h = catalog.searchHabitatByID(id);
            if (!h) { cout << RED << "  ❌ Habitat not found.\n" << RESET; }
            else {
                cout << YELLOW << "  Remove '" << h->getName() << "'? (y/n): " << RESET;
                char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (c == 'y' || c == 'Y') {
                    catalog.removeHabitat(id);
                    cout << GREEN << "  ✅ Habitat removed.\n" << RESET;
                }
            }
        }
        pauseScreen();
    }
}

// ======================== PHOTO HANDLERS ========================

void handleAddPhoto(Catalog& catalog) {
    printSectionHeader("ADD NEW PHOTO", "📸");
    string id     = getInput("Photo ID (e.g. P005)");
    string file   = getInput("Filename (e.g. elephant.jpg)");
    string loc    = getInput("Location");
    string date   = getInput("Date Captured (DD/MM/YYYY)");
    string photog = getInput("Photographer Name");
    string desc   = getInput("Description");
    string res    = getInput("Resolution (e.g. 24 MP)");

    Photo* p = new Photo(id, file, loc, date, photog, desc, res);
    catalog.addPhoto(p);
    cout << GREEN << "\n  ✅ Photo '" << file << "' added to gallery!\n" << RESET;
}

void handlePhotographyMenu(Catalog& catalog) {
    while (true) {
        displayPhotographyMenu();
        int choice = getMenuChoice(1, 7);

        if (choice == 7) break;

        if (choice == 1) {
            handleAddPhoto(catalog);
        }
        else if (choice == 2) {
            printSectionHeader("PHOTOGRAPHY GALLERY", "📸");
            catalog.displayAllPhotos();
        }
        else if (choice == 3) {
            string id = getInput("Enter Photo ID");
            Photo* p  = catalog.searchPhotoByID(id);
            if (p) p->displayPhoto();
            else cout << RED << "  ❌ Photo not found.\n" << RESET;
        }
        else if (choice == 4) {
            string loc = getInput("Enter Location");
            auto results = catalog.searchPhotoByLocation(loc);
            if (results.empty()) cout << RED << "  ❌ No photos found for location '" << loc << "'.\n" << RESET;
            else for (Photo* p : results) p->displayPhoto();
        }
        else if (choice == 5) {
            string pid = getInput("Enter Photo ID");
            string aid = getInput("Enter Species ID");
            if (catalog.linkPhotoToAnimal(pid, aid)) {
                cout << GREEN << "  ✅ Photo linked to species successfully!\n" << RESET;
            } else {
                cout << RED << "  ❌ Could not link: invalid Photo ID or Species ID.\n" << RESET;
            }
        }
        else if (choice == 6) {
            string id = getInput("Enter Photo ID to remove");
            Photo* p  = catalog.searchPhotoByID(id);
            if (!p) { cout << RED << "  ❌ Photo not found.\n" << RESET; }
            else {
                cout << YELLOW << "  Remove '" << p->getFilename() << "'? (y/n): " << RESET;
                char c; cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (c == 'y' || c == 'Y') {
                    catalog.removePhoto(id);
                    cout << GREEN << "  ✅ Photo removed.\n" << RESET;
                }
            }
        }
        pauseScreen();
    }
}

// ======================== CONSERVATION HANDLERS ========================

void handleConservationMenu(Catalog& catalog) {
    while (true) {
        displayConservationMenu();
        int choice = getMenuChoice(1, 4);

        if (choice == 4) break;

        if (choice == 1) {
            printSectionHeader("FULL CONSERVATION REPORT", "🌿");
            catalog.displayConservationReport();
        }
        else if (choice == 2) {
            catalog.displayEndangeredSpecies();
        }
        else if (choice == 3) {
            string status = getInput("Enter Conservation Status to search");
            auto results  = catalog.searchAnimalByStatus(status);
            if (results.empty()) {
                cout << RED << "  ❌ No species with status '" << status << "' found.\n" << RESET;
            } else {
                cout << GREEN << "  Found " << results.size() << " species:\n\n" << RESET;
                for (Animal* a : results) {
                    a->displayDetails();  // POLYMORPHISM: virtual dispatch
                }
            }
        }
        pauseScreen();
    }
}

// ======================== WILDLIFE DATABASE MENU ========================

void handleWildlifeMenu(Catalog& catalog) {
    while (true) {
        displayWildlifeMenu();
        int choice = getMenuChoice(1, 6);

        if (choice == 6) break;

        if (choice == 1) {
            handleAddSpecies(catalog);
            pauseScreen();
        }
        else if (choice == 2) {
            printSectionHeader("ALL SPECIES", "🦁");
            catalog.displayAllAnimals();
            pauseScreen();
        }
        else if (choice == 3) {
            handleSearchSpecies(catalog);
        }
        else if (choice == 4) {
            handleRemoveSpecies(catalog);
            pauseScreen();
        }
        else if (choice == 5) {
            handleHabitatMenu(catalog);
        }
    }
}

// ======================== MAIN ========================

int main() {
    system("chcp 65001 > nul");
    clearScreen();
    printBanner();

    cout << YELLOW << "  Initializing Wildlife Catalog...\n" << RESET;

    // Create the catalog object (COMPOSITION - main container)
    Catalog catalog("Global Wildlife Photography Catalog 2024");

    // Load sample data to demonstrate the system
    catalog.loadSampleData();

    cout << GREEN << "  ✅ Sample data loaded successfully!\n" << RESET;
    cout << CYAN  << "  📦 " << catalog.getTotalAnimals()  << " species, "
                             << catalog.getTotalHabitats() << " habitats, "
                             << catalog.getTotalPhotos()   << " photos ready.\n" << RESET;

    pauseScreen();

    // Main application loop
    bool running = true;
    while (running) {
        clearScreen();
        printBanner();
        displayMainMenu();

        int choice = getMenuChoice(1, 5);

        switch (choice) {
            case 1:
                handleWildlifeMenu(catalog);
                break;
            case 2:
                handlePhotographyMenu(catalog);
                break;
            case 3:
                handleConservationMenu(catalog);
                break;
            case 4:
                clearScreen();
                catalog.displayStatistics();
                pauseScreen();
                break;
            case 5:
                running = false;
                break;
        }
    }

    clearScreen();
    cout << CYAN << "\n  ╔═════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║ " << BOLD << GREEN << "  Thank you for using the Wildlife Conservation Platform! 🌍" << RESET << CYAN << " ║\n";
    cout << "  ║ " << YELLOW << "  Every species matters. Every habitat counts.               " << CYAN << "  ║\n";
    cout << "  ║ " << MAGENTA << "  Together we protect wildlife for future generations. 🌿   " << CYAN << "  ║\n";
    cout << "  ╚═════════════════════════════════════════════════════════════════╝\n" << RESET << endl;

    return 0;
}