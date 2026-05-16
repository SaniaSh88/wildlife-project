#ifndef HABITAT_H
#define HABITAT_H

#include <string>
#include <vector>
using namespace std;

// ============================================================
// Habitat Class - Demonstrates ENCAPSULATION and COMPOSITION
// Contains a list of species names (Composition via vector<string>)
// ============================================================
class Habitat {
private:
    // Private data members (Encapsulation)
    string habitatID;
    string name;
    string biomeType;
    string country;
    double latitude;
    double longitude;
    double areaKmSquared;
    vector<string> speciesNames;  // COMPOSITION: Habitat has Species names

public:
    // Constructors
    Habitat();
    Habitat(string id, string name, string biome, string country,
            double lat, double lon, double area);

    // Destructor
    ~Habitat();

    // --- Getters ---
    string getHabitatID()     const;
    string getName()          const;
    string getBiomeType()     const;
    string getCountry()       const;
    double getLatitude()      const;
    double getLongitude()     const;
    double getAreaKmSquared() const;
    vector<string> getSpeciesNames() const;
    int    getSpeciesCount()  const;

    // --- Setters ---
    void setHabitatID(const string& id);
    void setName(const string& name);
    void setBiomeType(const string& biome);
    void setCountry(const string& country);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setAreaKmSquared(double area);

    // Species management
    void addSpecies(const string& speciesName);
    void removeSpecies(const string& speciesName);

    // Display methods
    void displayHabitatInfo() const;
    void displayCompact()     const;
};

#endif // HABITAT_H