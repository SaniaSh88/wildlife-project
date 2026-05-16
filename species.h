#ifndef SPECIES_H
#define SPECIES_H

#include "Animal.h"
#include <string>
using namespace std;

// ============================================================
// Species Class - DERIVED from Animal (Abstract Base Class)
// Demonstrates:
//   - INHERITANCE   : Extends Animal using public inheritance
//   - POLYMORPHISM  : Overrides virtual methods from Animal
//   - ENCAPSULATION : Own private members with getters/setters
// ============================================================
class Species : public Animal {   // INHERITANCE: Species IS-A Animal
private:
    // Additional members specific to Species (Encapsulation)
    string diet;
    string averageWeight;
    string reproductionType;
    int    populationEstimate;

public:
    // Constructors
    Species();
    Species(string id, string common, string scientific,
            string habitat, string status,
            string diet, string weight,
            string reproType, int population);

    // Destructor
    ~Species();

    // --- Getters ---
    string getDiet()             const;
    string getAverageWeight()    const;
    string getReproductionType() const;
    int    getPopulationEstimate() const;

    // --- Setters ---
    void setDiet(const string& diet);
    void setAverageWeight(const string& weight);
    void setReproductionType(const string& type);
    void setPopulationEstimate(int population);

    // OVERRIDE pure virtual method (POLYMORPHISM + satisfies ABSTRACTION requirement)
    string getInfo() const override;

    // OVERRIDE virtual method from Animal (POLYMORPHISM)
    void displayDetails() const override;

    // OVERRIDE type identifier
    string getType() const override { return "Species"; }

    // Compact display for list views
    void displayCompact() const;

private:
    // Helper to get color-coded conservation status string
    string getStatusColor() const;
};

#endif // SPECIES_H