/*
-----------------------------------------------------------------------------
 File: publicationFactory.cpp
 Description: Implementation of PublicationFactory class. Creates appropriate
              publication objects based on type codes using Factory pattern.
              Handles error cases for invalid publication types.
 Author: Sharjeel Khan
 Assumptions: Fiction, Children, and Periodical classes have default constructors.
-----------------------------------------------------------------------------
*/
#include "publicationFactory.h"

using namespace std;

// Constants for publication type codes
const char FICTION_CODE = 'F';
const char CHILDREN_CODE = 'C';
const char PERIODICAL_CODE = 'P';

// ----------------------------------------------------------------------------
// createPublication
// Factory method to create publication objects based on type code
// Returns pointer to new publication object or nullptr for invalid type
// Error message displayed for invalid codes
Media* PublicationFactory::createPublication(char type) const {
    switch (type) {
        case FICTION_CODE:
            return new Fiction();
            
        case CHILDREN_CODE:
            return new Children();
            
        case PERIODICAL_CODE:
            return new Periodical();
            
        default:
            cout << "ERROR: '" << type << "' is not a valid LibItem type." << endl;
            return nullptr;
    }
}