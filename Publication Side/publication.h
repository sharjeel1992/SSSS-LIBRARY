/*
-----------------------------------------------------------------------------
 File: publication.h
 Description: Abstract base class for all library publications. Defines the
              common interface and data members shared by Fiction, Children's,
              and Periodical publications.
 Author: Sharjeel Khan
 Assumptions: All publications have title and year. Only Fiction and 
              Children's publications have authors.
-----------------------------------------------------------------------------
*/

#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "media.h"
#include <string>
#include <iostream>

using namespace std;

class Publication : public Media {
protected:
    string author;                    // Author name (empty for periodicals)
    string title;                     // Publication title
    int year;                         // Year of publication
    int copies;                       // Number of available copies

public:

    // Default Constructor
    Publication();
    
    // Ensures proper cleanup of derived classes
    virtual ~Publication();
    
    // Mutator methods
    void setAuthor(const string& a);
    void setTitle(const string& t);
    void setYear(int y);
    void setCopies(int c);
    
   
    // Accessor methods
    string getAuthor() const;
    string getTitle() const;
    int getYear() const;
    int getCopies() const override;
    
    // copies incremented by 1
    void increaseCopies();
    

    // copies decremented by 1
    void decreaseCopies();
    

    // Pure virtual functions - must be implemented by derived classes
    virtual void setData(istream& in) = 0;
    virtual void display(ostream& out) const = 0;
    virtual bool operator==(const Media& other) const = 0;
    virtual bool operator<(const Media& other) const = 0;
    virtual Media* create() const = 0;
    virtual Media* clone() const = 0;
};

#endif // PUBLICATION_H


