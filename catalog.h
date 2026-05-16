#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <vector>
#include "Animal.h"
#include "Species.h"
#include "Habitat.h"
#include "Photo.h"
using namespace std;

// ============================================================
// Catalog Class - MAIN MANAGEMENT SYSTEM
// Demonstrates:
//   - COMPOSITION : Contains vectors of Animal*, Habitat*, Photo*
//   - POLYMORPHISM: Stores Animal* (base class pointers) pointing
//                   to Species objects - runtime polymorphism
// ============================================================
class Catalog {
private:
    string catalogName;
    // COMPOSITION: Catalog has-many Animals, Habitats, and Photos
    vector<Animal*>   animals;    // Stores Animal* (polymorphic - can hold Species*)
    vector<Habitat*>  habitats;
    vector<Photo*>    photos;

public:
    // Constructor & Destructor
    Catalog(const string& name);
    ~Catalog();  // Cleans up all dynamically allocated objects

    // ---- Animal/Species Management ----
    void    addAnimal(Animal* animal);
    bool    removeAnimal(const string& id);
    Animal* searchAnimalByID(const string& id) const;
    vector<Animal*> searchAnimalByName(const string& name) const;
    vector<Animal*> searchAnimalByStatus(const string& status) const;
    vector<Animal*> getAllAnimals() const;
    void    displayAllAnimals() const;
    void    displayEndangeredSpecies() const;

    // ---- Habitat Management ----
    void      addHabitat(Habitat* habitat);
    bool      removeHabitat(const string& id);
    Habitat*  searchHabitatByID(const string& id) const;
    vector<Habitat*> searchHabitatByBiome(const string& biome) const;
    vector<Habitat*> getAllHabitats() const;
    void      displayAllHabitats() const;

    // ---- Photo Management ----
    void    addPhoto(Photo* photo);
    bool    removePhoto(const string& id);
    Photo*  searchPhotoByID(const string& id) const;
    vector<Photo*> searchPhotoByLocation(const string& location) const;
    vector<Photo*> getAllPhotos() const;
    void    displayAllPhotos() const;

    // Link a photo to an animal
    bool    linkPhotoToAnimal(const string& photoID, const string& animalID);

    // ---- Statistics ----
    int  getTotalAnimals()  const;
    int  getTotalHabitats() const;
    int  getTotalPhotos()   const;
    void displayStatistics()     const;

    // ---- Conservation Reports ----
    void displayConservationReport() const;

    // ---- Sample Data Loader ----
    void loadSampleData();

    // ---- Catalog Info ----
    string getCatalogName() const;
};

#endif // CATALOG_H