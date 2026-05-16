#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <vector>
#include "Photo.h"
using namespace std;

// ============================================================
// Animal Class - ABSTRACT BASE CLASS
// Demonstrates:
//   - ABSTRACTION     : Pure virtual method getInfo() = 0
//   - POLYMORPHISM    : Virtual methods overridden in derived classes
//   - ENCAPSULATION   : Protected members accessible to derived classes
//   - COMPOSITION     : Contains a vector of Photo pointers
// ============================================================
class Animal {
protected:
    // Protected members: accessible to derived classes (Species)
    string animalID;
    string commonName;
    string scientificName;
    string habitat;
    string conservationStatus;
    vector<Photo*> photos;  // COMPOSITION: Animal has Photos

public:
    // Constructor & Virtual Destructor (important for polymorphism)
    Animal();
    Animal(string id, string common, string scientific,
           string habitat, string status);
    virtual ~Animal();  // Virtual destructor for proper cleanup

    // --- Getters ---
    string getAnimalID()           const;
    string getCommonName()         const;
    string getScientificName()     const;
    string getHabitat()            const;
    string getConservationStatus() const;
    int    getPhotoCount()         const;

    // --- Setters ---
    void setAnimalID(const string& id);
    void setCommonName(const string& name);
    void setScientificName(const string& name);
    void setHabitat(const string& hab);
    void setConservationStatus(const string& status);

    // Photo management (Composition)
    void addPhoto(Photo* photo);
    void removePhoto(const string& photoID);
    vector<Photo*> getPhotos() const;
    void displayPhotos() const;

    // PURE VIRTUAL METHOD - makes Animal an abstract class
    // Derived classes MUST implement this (Abstraction + Polymorphism)
    virtual string getInfo() const = 0;

    // VIRTUAL METHODS - can be overridden in derived classes (Polymorphism)
    virtual void displayDetails() const;
    virtual string getType() const { return "Animal"; }
};

#endif // ANIMAL_H