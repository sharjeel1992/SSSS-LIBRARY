/*
 -----------------------------------------------------------------------------
 File: clientHash.h
 Description: Custom hash table implementation for Client objects. Uses
              4-digit client ID as hash key for O(1) average lookup time.
              Implements separate chaining for collision resolution.
 Author: Sharjeel Khan
 Assumptions: Client IDs are 4-digit integers (1000-9999)
              Hash function distributes IDs reasonably well
              Data format is "ID lastName firstName" with spaces
 -----------------------------------------------------------------------------
*/

#ifndef CLIENT_HASH_H
#define CLIENT_HASH_H

#include "client.h"

class ClientHash {
public:
    // Default Constructor
    ClientHash();
    

    // Destructor
    ~ClientHash();

    // Inserts client into hash table using ID as key
    bool insert(Client* client);
    
    // Finds client by ID in hash table
    bool retrieve(int id, Client*& found) const;

    // Removes client with specified ID from hash table
    bool remove(int id);

    // Displays all clients in hash table order
    void display() const;

    // Shows hash table statistics for debugging/analysis
    void displayStats() const;

    // Removes all elements from hash table
    void clear();

private:
    // Hash table node for separate chaining
    struct HashNode {
        Client* data;                 // Pointer to client object
        HashNode* next;               // Next node in chain
        
        HashNode(Client* client) : data(client), next(nullptr) {}
    };

    static const int TABLE_SIZE = 1009;  // Prime number for better distribution
    HashNode* table[TABLE_SIZE];          // Array of hash bucket heads

    // Computes hash value for given client ID
    int hashFunction(int id) const;
    
    // Recursively clears a single hash chain
    void clearChain(HashNode* node);
};

#endif // CLIENT_HASH_H

