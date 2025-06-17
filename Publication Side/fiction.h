/*
-----------------------------------------------------------------------------
 File: fiction.h
 Description: Fiction class representing fiction publications in the library.
              Fiction books are sorted by author, then by title.
              Library maintains 5 copies of each fiction publication.
 Author: Sharjeel Khan
 Assumptions: Fiction publications have author, title, and year fields
-----------------------------------------------------------------------------
*/

#ifndef FICTION_H
#define FICTION_H

#include "publication.h"

class Fiction : public Publication {
public:

    // Initializes fiction publication with 5 copies
    Fiction();
    
    // Virtual destructor for proper cleanup
    virtual ~Fiction();

    // Reads fiction data from input stream (author, title, year)
    virtual void setData(istream& in) override;
    
    // Outputs fiction data in formatted columns
    virtual void display(ostream& out) const override;

    // Compares fiction publications for equality (same author and title)
    virtual bool operator==(const Media& other) const override;

    // Compares for sorting by author, then title
    virtual bool operator<(const Media& other) const override;

    // Factory method to create new Fiction object
    virtual Media* create() const override;
    
    // Creates deep copy of this Fiction object
    virtual Media* clone() const override;
};

#endif // FICTION_H

