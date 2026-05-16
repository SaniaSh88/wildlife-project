#include "Photo.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ANSI Color codes for beautiful console output
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
Photo::Photo() : photoID(""), filename(""), location(""), dateCaptured(""),
                 photographer(""), description(""), resolution("") {}

// Parameterized constructor
Photo::Photo(string id, string file, string loc, string date,
             string photog, string desc, string res)
    : photoID(id), filename(file), location(loc), dateCaptured(date),
      photographer(photog), description(desc), resolution(res) {}

// Destructor
Photo::~Photo() {}

// --- Getter Implementations ---
string Photo::getPhotoID()      const { return photoID; }
string Photo::getFilename()     const { return filename; }
string Photo::getLocation()     const { return location; }
string Photo::getDateCaptured() const { return dateCaptured; }
string Photo::getPhotographer() const { return photographer; }
string Photo::getDescription()  const { return description; }
string Photo::getResolution()   const { return resolution; }

// --- Setter Implementations ---
void Photo::setPhotoID(const string& id)          { photoID = id; }
void Photo::setFilename(const string& file)        { filename = file; }
void Photo::setLocation(const string& loc)         { location = loc; }
void Photo::setDateCaptured(const string& date)    { dateCaptured = date; }
void Photo::setPhotographer(const string& photog)  { photographer = photog; }
void Photo::setDescription(const string& desc)     { description = desc; }
void Photo::setResolution(const string& res)       { resolution = res; }

// Full photo display with ANSI colors and box drawing characters
void Photo::displayPhoto() const {
    cout << CYAN << "  ╔══════════════════════════════════════════════════════╗" << RESET << endl;
    cout << CYAN << "  ║ " << BOLD << YELLOW << "📸 PHOTO DETAILS" << RESET << CYAN << "                                       ║" << RESET << endl;
    cout << CYAN << "  ╠══════════════════════════════════════════════════════╣" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "ID         : " << RESET << WHITE << left << setw(40) << photoID      << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Filename   : " << RESET << WHITE << left << setw(40) << filename     << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Location   : " << RESET << WHITE << left << setw(40) << location     << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Date       : " << RESET << WHITE << left << setw(40) << dateCaptured << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Photographer: " << RESET << WHITE << left << setw(39) << photographer << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Resolution : " << RESET << WHITE << left << setw(40) << resolution   << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ║ " << RESET << GREEN  << "Description: " << RESET << YELLOW << left << setw(40) << description  << CYAN << "║" << RESET << endl;
    cout << CYAN << "  ╚══════════════════════════════════════════════════════╝" << RESET << endl;
}

// Compact single-line display for lists
void Photo::displayPhotoCompact() const {
    cout << CYAN << "  [" << YELLOW << photoID << CYAN << "] "
         << WHITE << left << setw(25) << filename
         << GREEN << left << setw(20) << location
         << MAGENTA << left << setw(15) << dateCaptured
         << BLUE   << resolution
         << RESET  << endl;
}