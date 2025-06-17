/*
-----------------------------------------------------------------------------
 File: periodical.cpp
 Description: Implementation of Periodical class. Handles periodical 
              publications (magazines, journals) which are sorted by year,
              then month, then title. Library owns 1 copy of each periodical.
 Author: Sharjeel Khan
 Assumptions: Input data format is "P title, month year"
              Periodicals do not have authors
-----------------------------------------------------------------------------
*/
#include "periodical.h"
#include <iomanip>

// Constants  
const int PERIODICAL_COPIES = 1;
const int AVAIL_WIDTH = 6;
const int TITLE_WIDTH = 40;
const int MONTH_WIDTH = 8;
const int YEAR_WIDTH = 6;
const int MAX_TITLE_DISPLAY = 39;
const int DEFAULT_MONTH = 0;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes periodical with 1 copy and default month
// Periodical object created with 1 available copy
Periodical::Periodical() : month(DEFAULT_MONTH) {
    copies = PERIODICAL_COPIES;
}

// ----------------------------------------------------------------------------
// Destructor
// Virtual destructor for proper cleanup
Periodical::~Periodical() = default;

// ----------------------------------------------------------------------------
// setData
// Reads periodical data from input stream in format: title, month year
// Periodical object populated with data from stream
void Periodical::setData(istream& in) {
    getline(in >> ws, title, ',');        // Read title until comma
    in >> month >> year;                  // Read month and year as integers
}

// ----------------------------------------------------------------------------
// display
// Outputs periodical information in formatted columns
// Periodical data written to stream in tabular format
void Periodical::display(ostream& out) const {
    out << left << setw(AVAIL_WIDTH) << copies
        << setw(TITLE_WIDTH) << title.substr(0, MAX_TITLE_DISPLAY)
        << right << setw(MONTH_WIDTH) << month
        << setw(YEAR_WIDTH) << year << endl;
}

// ----------------------------------------------------------------------------
// operator==
// Returns true if both are periodicals with same title, year, and month
bool Periodical::operator==(const Media& other) const {
    const Periodical* p = dynamic_cast<const Periodical*>(&other);
    return p && title == p->title && year == p->year && month == p->month;
}

// ----------------------------------------------------------------------------
// operator<
// Compares periodicals for sorting (year first, then month, then title)
// Returns true if this periodical should sort before other
bool Periodical::operator<(const Media& other) const {
    const Periodical* p = dynamic_cast<const Periodical*>(&other);
    if (!p) return false;
    
    // Sort by year first, then month, then title
    if (year != p->year) {
        return year < p->year;
    }
    if (month != p->month) {
        return month < p->month;
    }
    return title < p->title;
}

// ----------------------------------------------------------------------------
// create
// Factory method to create new Periodical object
// Returns pointer to new Periodical object
Media* Periodical::create() const {
    return new Periodical();
}

// ----------------------------------------------------------------------------
// clone
// Creates deep copy of this Periodical object
// Returns pointer to new Periodical with same data
Media* Periodical::clone() const {
    Periodical* p = new Periodical();
    p->title = this->title;
    p->year = this->year;
    p->month = this->month;
    p->copies = this->copies;
    // Note: Periodicals don't have authors
    return p;
}