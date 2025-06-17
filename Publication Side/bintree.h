/*
-----------------------------------------------------------------------------
 File: bintree.h
 Description: Binary Search Tree implementation for Media objects. Maintains
              sorted order based on Media comparison operators. Container only
              stores pointers
 Author: Sharjeel Khan
 Assumptions: Media objects have properly implemented < and == operators
              Media objects are managed elsewhere (not owned by tree)
-----------------------------------------------------------------------------
*/

#ifndef BINTREE_H
#define BINTREE_H

#include "media.h"
#include <iostream>

class BinTree {
public:
    // Creates empty binary search tree
    BinTree();
    
    // Cleans up all tree nodes (but not the Media objects they point to)
    ~BinTree();
   
    // Inserts Media pointer into tree in sorted order
    bool insert(Media* media);
    
    
    // Finds Media object matching target in the tree
    bool retrieve(const Media& target, Media*& found) const;
    

    // Displays all Media objects in sorted order (in-order traversal)
    void display() const;
    

    // Removes all nodes from tree without deleting Media objects
    void makeEmpty();

private:
    struct Node {
        Media* data;                  // Pointer to Media object 
        Node* left;                   // Left child pointer
        Node* right;                  // Right child pointer

        // Node constructor
        Node(Media* m) : data(m), left(nullptr), right(nullptr) {}
    };

    Node* root;                       // Root of the binary search tree

    // Private helper methods for recursive operations
    
    // makeEmpty helper 
    void makeEmpty(Node*& node);
    
    // insert helper
    bool insert(Node*& node, Media* media);
    
    // retrieve helper 
    bool retrieve(Node* node, const Media& target, Media*& found) const;
    
    // display helper
    void display(Node* node) const;
    
    // destroy helper 
    void destroy(Node* node);
};

#endif // BINTREE_H