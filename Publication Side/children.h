/*
-----------------------------------------------------------------------------
 File: children.h
 Description: Children class representing children's books in the library.
              Children's books are sorted by title, then by author.
              Library maintains 5 copies of each children's publication.
 Author: Sharjeel Khan
 Assumptions: Children's publications have author, title, and year fields
-----------------------------------------------------------------------------
*/

#ifndef CHILDREN_H
#define CHILDREN_H

#include "publication.h"

class Children : public Publication {
public:
    
   
    // Initializes children's publication with 5 copies
    Children();
    
    // Virtual destructor for proper cleanup
    virtual ~Children();

    // Reads children's data from input stream (author, title, year)
    virtual void setData(istream& in) override;

    // Outputs children's data in formatted columns (title first, then author)
    virtual void display(ostream& out) const override;
 
    // Compares children's publications for equality (same title and author)
    virtual bool operator==(const Media& other) const override;
 
    // Compares for sorting by title, then author
    virtual bool operator<(const Media& other) const override;

    // Factory method to create new Children object
    virtual Media* create() const override;
    
    // Creates deep copy of this Children object
    virtual Media* clone() const override;
};

#endif // CHILDREN_H
