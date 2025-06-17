// -----------------------------------------------------------------------------
// File: media.h
// Description: Abstract base class representing a general media item in the
//              library system. Defines the interface that all specific types
//              of library items must implement.
// Author: Sharjeel Khan
// Assumptions: All media items support data input/output, comparison operations,
//              and factory methods for creation and cloning
// -----------------------------------------------------------------------------

#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>

using namespace std;

class Media {
public:
    // Creates a media object with default values
    Media() = default;
    
    // Ensures proper cleanup of derived classes
    virtual ~Media() = default;


    // Reads media item data from input stream
    virtual void setData(istream&) = 0;

    // Outputs media item information to output stream
    virtual void display(ostream& out) const = 0;

    // Compares two media items for equality
    virtual bool operator==(const Media& other) const = 0;
    

    // Compares media items for ordering (used for sorting)
    virtual bool operator<(const Media& other) const = 0;


    // Factory method to create new instance of same media type
    virtual Media* create() const = 0;
    
 
    // Creates deep copy of this media object
    virtual Media* clone() const = 0;


    // Returns number of available copies of this media item
    virtual int getCopies() const = 0;
};

#endif // MEDIA_H