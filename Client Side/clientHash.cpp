/*
-----------------------------------------------------------------------------
 File: clientHash.cpp
 Description: Implementation of custom hash table for Client objects.
              Uses separate chaining for collision resolution and provides
              O(1) average case lookup time for client retrieval.
 Author: Sharjeel Khan
 Assumptions: Client IDs are distributed reasonably well across hash range
              Memory allocation succeeds for new nodes
              Data format is "ID lastName firstName" with spaces
 -----------------------------------------------------------------------------
*/

#include "clientHash.h"
#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes hash table.Empty hash table ready for insertions
ClientHash::ClientHash() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up all hash table resources
ClientHash::~ClientHash() {
    clear();
}

// ----------------------------------------------------------------------------
// hashFunction
// Computes hash value for client ID using modulo operation
// Returns hash value in valid table range [0, TABLE_SIZE-1]
int ClientHash::hashFunction(int id) const {
    // Simple modulo hash - works well for 4-digit IDs with prime table size
    return id % TABLE_SIZE;
}

// ----------------------------------------------------------------------------
// insert
// Inserts client into appropriate hash bucket
// Client inserted if not duplicate, hash table updated
bool ClientHash::insert(Client* client) {
    if (client == nullptr) {
        return false;
    }
    int hashValue = hashFunction(client->getID());
    HashNode* current = table[hashValue];

    // Check for duplicates in the chain
    while (current != nullptr) {
        if (current->data->getID() == client->getID()) {
            return false; // Duplicate ID found, don't insert
        }
        current = current->next;
    }

    // Insert at beginning of chain
    HashNode* newNode = new HashNode(client);
    newNode->next = table[hashValue];
    table[hashValue] = newNode;
    
    return true;
}

// ----------------------------------------------------------------------------
// retrieve
// Searches for client by ID in hash table
//found points to matching Client or nullptr, returns success status
bool ClientHash::retrieve(int id, Client*& found) const {
    int hashValue = hashFunction(id);
    HashNode* current = table[hashValue];

    // Search through the chain at this hash bucket
    while (current != nullptr) {
        if (current->data->getID() == id) {
            found = current->data;
            return true;
        }
        current = current->next;
    }

    found = nullptr;
    return false;
}

// ----------------------------------------------------------------------------
// remove
// Removes client with specified ID from hash table
//Client removed and deallocated if found
bool ClientHash::remove(int id) {
    int hashValue = hashFunction(id);
    HashNode* current = table[hashValue];
    HashNode* previous = nullptr;

    // Search for the node to remove
    while (current != nullptr) {
        if (current->data->getID() == id) {
            // Found the node to remove
            if (previous == nullptr) {
                // Removing first node in chain
                table[hashValue] = current->next;
            } else {
                // Removing middle or end node
                previous->next = current->next;
            }

            delete current->data;  // Delete the client object
            delete current;        // Delete the hash node
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false; // Client not found
}

// ----------------------------------------------------------------------------
// display
// Displays all clients in hash table bucket order
// All clients displayed with their information
void ClientHash::display() const {
    cout << "CLIENT HASH TABLE CONTENTS:" << endl;
    cout << "===========================" << endl;

    bool hasClients = false;
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = table[i];
        if (current != nullptr) {
            while (current != nullptr) {
                current->data->display();
                current = current->next;
                hasClients = true;
            }
        }
    }

    if (!hasClients) {
        cout << "No clients in hash table." << endl;
    }
}

// ----------------------------------------------------------------------------
// displayStats
// Shows hash table statistics for analysis
// Bucket usage statistics displayed
void ClientHash::displayStats() const {
    int usedBuckets = 0;
    int totalClients = 0;
    int maxChainLength = 0;

    for (int i = 0; i < TABLE_SIZE; ++i) {
        int chainLength = 0;
        HashNode* current = table[i];
        
        if (current != nullptr) {
            usedBuckets++;
            while (current != nullptr) {
                chainLength++;
                totalClients++;
                current = current->next;
            }
        }
        
        if (chainLength > maxChainLength) {
            maxChainLength = chainLength;
        }
    }

    cout << "Hash Table Statistics:" << endl;
    cout << "Total buckets: " << TABLE_SIZE << endl;
    cout << "Used buckets: " << usedBuckets << endl;
    cout << "Total clients: " << totalClients << endl;
    cout << "Max chain length: " << maxChainLength << endl;
    if (totalClients > 0) {
        cout << "Load factor: " << (double)totalClients / TABLE_SIZE << endl;
    }
}

// ----------------------------------------------------------------------------
// clear
// Removes all elements from hash table
// All clients and nodes deallocated, table reset to empty
void ClientHash::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        clearChain(table[i]);
        table[i] = nullptr;
    }
}

// ----------------------------------------------------------------------------
// clearChain
// Recursively deallocates all nodes in a hash chain
// All nodes in chain deallocated including client objects
void ClientHash::clearChain(HashNode* node) {
    if (node != nullptr) {
        clearChain(node->next);
        delete node->data;  // Delete the client object
        delete node;        // Delete the hash node
    }
}