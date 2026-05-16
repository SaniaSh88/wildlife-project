#ifndef PHOTO_H
#define PHOTO_H

#include <string>
using namespace std;

// ============================================================
// Photo Class - Demonstrates ENCAPSULATION
// All data members are private; access via public getters/setters
// ============================================================
class Photo {
private:
    // Private data members (Encapsulation)
    string photoID;
    string filename;
    string location;
    string dateCaptured;
    string photographer;
    string description;
    string resolution;

public:
    // Constructors
    Photo();
    Photo(string id, string file, string loc, string date,
          string photographer, string desc, string res);

    // Destructor
    ~Photo();

    // --- Getters (public interface for private data) ---
    string getPhotoID()     const;
    string getFilename()    const;
    string getLocation()    const;
    string getDateCaptured()const;
    string getPhotographer()const;
    string getDescription() const;
    string getResolution()  const;

    // --- Setters (controlled modification of private data) ---
    void setPhotoID(const string& id);
    void setFilename(const string& file);
    void setLocation(const string& loc);
    void setDateCaptured(const string& date);
    void setPhotographer(const string& photographer);
    void setDescription(const string& desc);
    void setResolution(const string& res);

    // Display method
    void displayPhoto() const;
    void displayPhotoCompact() const;
};

#endif // PHOTO_H