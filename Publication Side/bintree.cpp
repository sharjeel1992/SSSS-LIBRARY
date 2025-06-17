/*
-----------------------------------------------------------------------------
 File: bintree.cpp
 Description: Implementation of Binary Search Tree for Media* objects.
              Maintains sorted order without owning the Media objects.
              Tree acts as pure container following professor's guidelines.
 Author: Sharjeel Khan
 Assumptions: Media objects exist for lifetime of tree usage
              Comparison operators work correctly for sorting
-----------------------------------------------------------------------------
*/

#include "bintree.h"

using namespace std;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes empty binary search tree
// Tree created with null root
BinTree::BinTree() : root(nullptr) {
}

// ----------------------------------------------------------------------------
// Destructor  
// Cleans up tree structure without deleting Media objects
// All tree nodes deallocated, Media objects preserved
BinTree::~BinTree() {
    makeEmpty();
}

// ----------------------------------------------------------------------------
// makeEmpty
// Removes all nodes from tree, preserving Media objects
// Tree is empty, ready for new insertions
void BinTree::makeEmpty() {
    destroy(root);
    root = nullptr;
}

// ----------------------------------------------------------------------------
// destroy
// Recursively deallocates tree nodes without touching Media objects
// All nodes in subtree deallocated, Media objects untouched
void BinTree::destroy(Node* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        // Delete the Media object - tree owns the publications
        delete node->data;
        delete node;
    }
}

// ----------------------------------------------------------------------------
// insert
// Public interface for inserting Media pointer into tree
// Media inserted in BST order if not duplicate
bool BinTree::insert(Media* media) {
    if (media == nullptr) {
        return false;
    }
    return insert(root, media);
}

// ----------------------------------------------------------------------------
// insert (private helper)
// Recursively inserts Media maintaining BST property
// Media inserted in correct position, tree remains valid BST
bool BinTree::insert(Node*& node, Media* media) {
    if (node == nullptr) {
        node = new Node(media);
        return true;
    } else if (*media < *node->data) {
        return insert(node->left, media);
    } else if (*node->data < *media) {
        return insert(node->right, media);
    } else {
        // Duplicate found (*media == *node->data)
        // Don't insert duplicates, return false
        return false;
    }
}

// ----------------------------------------------------------------------------
// retrieve
// Public interface for finding Media object in tree
// found set to matching Media* or nullptr
bool BinTree::retrieve(const Media& target, Media*& found) const {
    return retrieve(root, target, found);
}

// ----------------------------------------------------------------------------
// retrieve (private helper)
// Recursively searches for Media object matching target
// found points to matching Media* if exists, nullptr otherwise
bool BinTree::retrieve(Node* node, const Media& target, Media*& found) const {
    if (node == nullptr) {
        found = nullptr;
        return false;
    } else if (target == *node->data) {
        found = node->data;
        return true;
    } else if (target < *node->data) {
        return retrieve(node->left, target, found);
    } else {
        return retrieve(node->right, target, found);
    }
}

// ----------------------------------------------------------------------------
// display
// Public interface for displaying all Media objects in sorted order
// All Media objects displayed via in-order traversal
void BinTree::display() const {
    display(root);
}

// ----------------------------------------------------------------------------
// display (private helper)
// Performs in-order traversal to display Media objects in sorted order
// All Media objects in subtree displayed in ascending order
void BinTree::display(Node* node) const {
    if (node != nullptr) {
        display(node->left);          // Display left subtree first
        node->data->display(cout);    // Display current node
        display(node->right);         // Display right subtree last
    }
}