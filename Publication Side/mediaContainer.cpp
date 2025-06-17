/*
-----------------------------------------------------------------------------
 File: mediaContainer.cpp
 Description: Implementation for MediaContainer class. Manages separate
              binary search trees for Fiction, Children's, and Periodical
              publications with appropriate sorting and display.
 Author: Sharjeel Khan
 Assumptions: BinTree supports insert, retrieve, and display operations
              Dynamic casting successfully identifies publication types
-----------------------------------------------------------------------------
*/

#include "mediaContainer.h"
#include "fiction.h"
#include "children.h"
#include "periodical.h"
#include <iostream>

using namespace std;

// Constants for display headers
const char FICTION_TYPE = 'F';
const char CHILDREN_TYPE = 'C';
const char PERIODICAL_TYPE = 'P';

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes empty binary trees for all publication types
// MediaContainer created with three empty BinTree objects
MediaContainer::MediaContainer() = default;

// ----------------------------------------------------------------------------
// Destructor
// Cleans up all tree resources
// All BinTree objects properly destroyed
MediaContainer::~MediaContainer() = default;

// ----------------------------------------------------------------------------
// insert
// Inserts media item into appropriate tree based on dynamic type
// Item inserted into correct tree, returns success status
bool MediaContainer::insert(Media* item) {
    if (!item) {
        return false;
    }

    // Determine type and insert into appropriate tree
    if (dynamic_cast<Fiction*>(item)) {
        return fictionTree.insert(item);
    } else if (dynamic_cast<Children*>(item)) {
        return childrenTree.insert(item);
    } else if (dynamic_cast<Periodical*>(item)) {
        return periodicalTree.insert(item);
    }

    // Fixed: Use cout instead of cerr per assignment requirements
    cout << "ERROR: Unknown media type. Insert failed." << endl;
    return false;
}

// ----------------------------------------------------------------------------
// retrieve
// Finds media item in specified tree matching the target
// Post: Returns pointer to found item or nullptr if not found
Media* MediaContainer::retrieve(const Media& target, char type) const {
    const BinTree* tree = getTree(type);
    if (!tree) {
        return nullptr;
    }
    
    Media* found = nullptr;
    tree->retrieve(target, found);
    return found;
}

// ----------------------------------------------------------------------------
// displayAll
// Tree contents displayed with headers and formatting
void MediaContainer::displayAll(char type) const {
    const BinTree* tree = getTree(type);
    if (!tree) {
        return;
    }
    
    // Display appropriate header based on publication type
    switch (type) {
        case FICTION_TYPE:
            cout << "FICTION PUBLICATIONS" << endl;
            cout << "AVAIL AUTHOR                        TITLE                                    YEAR" << endl;
            break;
        case CHILDREN_TYPE:
            cout << "CHILDREN'S PUBLICATIONS" << endl;
            cout << "AVAIL TITLE                                   AUTHOR                         YEAR" << endl;
            break;
        case PERIODICAL_TYPE:
            cout << "PERIODICAL PUBLICATIONS" << endl;
            cout << "AVAIL TITLE                                         MONTH YEAR" << endl;
            break;
        default:
            cout << "ERROR: Invalid publication type for display." << endl;
            return;
    }
    
    // Display tree contents
    tree->display();
    cout << endl; // Add blank line after each section
}

// ----------------------------------------------------------------------------
// getTree
// Returns pointer to tree corresponding to type code
// Returns pointer to appropriate tree or nullptr for invalid type
BinTree* MediaContainer::getTree(char type) {
    switch (type) {
        case FICTION_TYPE: 
            return &fictionTree;
        case CHILDREN_TYPE: 
            return &childrenTree;
        case PERIODICAL_TYPE: 
            return &periodicalTree;
        default: 
            return nullptr;
    }
}

// ----------------------------------------------------------------------------
// getTree (const version)
// Returns const pointer to tree corresponding to type code
// Returns const pointer to appropriate tree or nullptr for invalid type
const BinTree* MediaContainer::getTree(char type) const {
    switch (type) {
        case FICTION_TYPE: 
            return &fictionTree;
        case CHILDREN_TYPE: 
            return &childrenTree;
        case PERIODICAL_TYPE: 
            return &periodicalTree;
        default: 
            return nullptr;
    }
}