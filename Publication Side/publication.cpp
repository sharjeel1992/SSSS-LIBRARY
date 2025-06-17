/*
-----------------------------------------------------------------------------
 File: publication.cpp  
 Description: Implementation of Publication base class. Provides common
              functionality for all publication types in the library system.
 Author: Sharjeel Khan
 Assumptions: Derived classes will set appropriate copy counts in their
              constructors (5 for Fiction/Children, 1 for Periodicals)
-----------------------------------------------------------------------------
*/

#include "publication.h"

// Constants
const int DEFAULT_YEAR = 0;
const int MIN_COPIES = 0;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes data members to default values
// Object created with empty strings and zero values
Publication::Publication() : author(""), title(""), year(DEFAULT_YEAR), copies(MIN_COPIES) {
}

// ----------------------------------------------------------------------------  
// Destructor
// Virtual destructor for proper cleanup of derived classes
Publication::~Publication() = default;

// ----------------------------------------------------------------------------
// setAuthor
// Sets the author name for this publication
// author data member updated
void Publication::setAuthor(const string& a) {
    author = a;
}

// ----------------------------------------------------------------------------
// setTitle  
// Sets the title for this publication
// title data member updated
void Publication::setTitle(const string& t) {
    title = t;
}

// ----------------------------------------------------------------------------
// setYear
// Sets the publication year
// year data member updated  
void Publication::setYear(int y) {
    year = y;
}

// ----------------------------------------------------------------------------
// setCopies
// Sets the number of available copies
// copies data member updated
void Publication::setCopies(int c) {
    copies = c;
}

// ----------------------------------------------------------------------------
// getAuthor
// Returns the author name
// Returns current author string
string Publication::getAuthor() const {
    return author;
}

// ----------------------------------------------------------------------------
// getTitle
// Returns the publication title  
// Returns current title string
string Publication::getTitle() const {
    return title;
}

// ----------------------------------------------------------------------------
// getYear
// Returns the publication year
// Returns current year value
int Publication::getYear() const {
    return year;
}

// ----------------------------------------------------------------------------
// getCopies
// Returns the number of available copies
// Returns current copies count
int Publication::getCopies() const {
    return copies;
}

// ----------------------------------------------------------------------------
// increaseCopies
// Increments the available copy count by one
// copies increased by 1
void Publication::increaseCopies() {
    ++copies;
}

// ----------------------------------------------------------------------------
// decreaseCopies
// Decrements the available copy count by one, minimum of 0
// copies decreased by 1, never goes below 0
void Publication::decreaseCopies() {
    if (copies > MIN_COPIES) {
        --copies;
    }
}