/*
-----------------------------------------------------------------------------
 File: children.cpp
 Description: Implementation of Children class. Handles children's book
              publications which are sorted by title then author. Library
              owns 5 copies of each children's publication.
 Author: Sharjeel Khan
 Assumptions: Input data format is "C author, title, year"
              Author and title are comma-separated strings
-----------------------------------------------------------------------------
*/

#include "children.h"
#include <iomanip>

//----------------------------------------------------------------------------
// Constuctor
// Set copies to 5 for children's publications
Children::Children() {
    copies = 5;
}

//----------------------------------------------------------------------------
// Destructor
Children::~Children() = default;

//----------------------------------------------------------------------------
// setData
// Format: C author, title, year (same as fiction)
void Children::setData(istream& in) {
    getline(in >> ws, author, ',');
    getline(in >> ws, title, ',');
    in >> year;
}
//----------------------------------------------------------------------------
//Display
//Format to match sample output: AVAIL TITLE AUTHOR YEAR
//Note: Children's displays title first, then author (different from fiction)
void Children::display(ostream& out) const {
    out << left << setw(6) << copies
        << setw(40) << title.substr(0, 39)
        << setw(30) << author.substr(0, 29)
        << right << setw(5) << year << endl;
}

//----------------------------------------------------------------------------
// operator==
// Returns true if both are children with same title, author
bool Children::operator==(const Media& other) const {
    const Children* c = dynamic_cast<const Children*>(&other);
    return c && title == c->title && author == c->author;
}

//----------------------------------------------------------------------------
// operator<
// Compares children for sorting (author,title,year)
bool Children::operator<(const Media& other) const {
    const Children* c = dynamic_cast<const Children*>(&other);
    if (!c) return false;
    // Sort by title first, then author
    if (title != c->title) return title < c->title;
    return author < c->author;
}

//----------------------------------------------------------------------------
// create
// Factory method to create new Children object
// Returns pointer to new Children object
Media* Children::create() const {
    return new Children();
}

//----------------------------------------------------------------------------
// clone
// Creates deep copy of this children object
// Returns pointer to new children with same data
Media* Children::clone() const {
    Children* c = new Children();
    c->author = this->author;
    c->title = this->title;
    c->year = this->year;
    c->copies = this->copies;
    return c;
}