/*
-----------------------------------------------------------------------------
 File: mediaContainer.h
 Description: Manages multiple BinTree containers for different media types.
              Provides unified interface for storing Fiction, Children's, and
              Periodical publications in separate sorted collections.
 Author: Sharjeel Khan
 Assumptions: BinTree class exists and supports Media storage
              Media types can be determined via dynamic_cast
-----------------------------------------------------------------------------
*/

#ifndef MEDIACONTAINER_H
#define MEDIACONTAINER_H

#include "bintree.h"
#include "media.h"

class MediaContainer {
public:

    // Initializes empty containers for all media types
    MediaContainer();
    

    // Cleans up all container resources
    ~MediaContainer();
    
    // Inserts media item into appropriate container based on type
    bool insert(Media* item); 
    

    // Finds and returns media item matching target in specified container
    Media* retrieve(const Media& target, char type) const;
    

    // Displays all items in specified container with headers
    void displayAll(char type) const;

private:
    BinTree fictionTree;              // Container for Fiction publications
    BinTree childrenTree;             // Container for Children's publications
    BinTree periodicalTree;           // Container for Periodical publications


    // Returns pointer to appropriate tree based on type code
    BinTree* getTree(char type);
    
 
    // Returns const pointer to appropriate tree based on type code
    const BinTree* getTree(char type) const;
};

#endif // MEDIACONTAINER_H
