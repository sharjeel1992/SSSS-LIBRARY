/*
-----------------------------------------------------------------------------
 File: periodical.h
 Description: Periodical class representing magazines and journals in the
              library. Periodicals are sorted by year, then month, then title.
              Library maintains 1 copy of each periodical publication.
 Author: Sharjeel Khan
 Assumptions: Periodicals have title, month, and year fields (no author)
 -----------------------------------------------------------------------------
*/
#ifndef PERIODICAL_H
#define PERIODICAL_H

#include "publication.h"

class Periodical : public Publication {
public:

    // Default Constructor
    Periodical();
    
    // Destructor
    virtual ~Periodical();

    // Reads periodical data from input stream (title, month, year)
    virtual void setData(istream& in) override;
    

    // Outputs periodical data in formatted columns
    virtual void display(ostream& out) const override;


    // Compares periodicals for equality (same title, month, and year)
    virtual bool operator==(const Media& other) const override;
    

    // Compares for sorting by year, then month, then title
    virtual bool operator<(const Media& other) const override;

    // Factory method to create new Periodical object
    virtual Media* create() const override;
    
 
    // Creates deep copy of this Periodical object
    virtual Media* clone() const override;

private:
    int month;           // Publication month (1-12)
};

#endif // PERIODICAL_H