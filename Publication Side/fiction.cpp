/*
-----------------------------------------------------------------------------
 File: fiction.cpp
 Description: Implementation of Fiction class. Handles fiction publications
              which are sorted by author then title. Library owns 5 copies
              of each fiction publication.
 Author: Sharjeel Khan 
 Assumptions: Input data format is "F author, title, year"
              Author and title are comma-separated strings
-----------------------------------------------------------------------------
*/

#include "fiction.h"
#include <iomanip>

// Constants
const int FICTION_COPIES = 5;
const int AVAIL_WIDTH = 6;
const int AUTHOR_WIDTH = 30;
const int TITLE_WIDTH = 40;
const int YEAR_WIDTH = 5;
const int MAX_AUTHOR_DISPLAY = 29;
const int MAX_TITLE_DISPLAY = 39;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes fiction publication with 5 copies
// Fiction object created with 5 available copies
Fiction::Fiction() {
    copies = FICTION_COPIES;
}

// ----------------------------------------------------------------------------
// Destructor  
// Virtual destructor for proper cleanup
Fiction::~Fiction() = default;

// ----------------------------------------------------------------------------
// setData
// Reads fiction data from input stream in format: author, title, year
// Fiction object populated with data from stream
void Fiction::setData(istream& in) {
    getline(in >> ws, author, ',');       // Read author until comma
    getline(in >> ws, title, ',');        // Read title until comma  
    in >> year;                           // Read year as integer
}

// ----------------------------------------------------------------------------
// display
// Outputs fiction information in formatted columns
// Fiction data written to stream in tabular format
void Fiction::display(ostream& out) const {
    out << left << setw(AVAIL_WIDTH) << copies
        << setw(AUTHOR_WIDTH) << author.substr(0, MAX_AUTHOR_DISPLAY)
        << setw(TITLE_WIDTH) << title.substr(0, MAX_TITLE_DISPLAY)
        << right << setw(YEAR_WIDTH) << year << endl;
}

// ----------------------------------------------------------------------------
// operator==
// Compares two fiction publications for equality
// Returns true if both are fiction with same author and title
bool Fiction::operator==(const Media& other) const {
    const Fiction* f = dynamic_cast<const Fiction*>(&other);
    return f && author == f->author && title == f->title;
}

// ----------------------------------------------------------------------------
// operator<
// Compares fiction publications for sorting (author first, then title)
// Returns true if this fiction should sort before other
bool Fiction::operator<(const Media& other) const {
    const Fiction* f = dynamic_cast<const Fiction*>(&other);
    if (!f) return false;
    
    // Sort by author first, then by title
    if (author != f->author) {
        return author < f->author;
    }
    return title < f->title;
}

// ----------------------------------------------------------------------------
// create
// Factory method to create new Fiction object
// Returns pointer to new Fiction object
Media* Fiction::create() const {
    return new Fiction();
}

// ----------------------------------------------------------------------------
// clone
// Creates deep copy of this Fiction object
// Returns pointer to new Fiction with same data
Media* Fiction::clone() const {
    Fiction* f = new Fiction();
    f->author = this->author;
    f->title = this->title;
    f->year = this->year;
    f->copies = this->copies;
    return f;
}