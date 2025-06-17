/*
-----------------------------------------------------------------------------
 File: clientManager.cpp
 Description: Implementation of ClientManager class. Manages library clients
              using custom hash table for efficient O(1) lookup operations.
              Handles client data parsing and file input processing.
 Author: Sharjeel Khan
 Assumptions: Client data format is "ID lastName firstName" with spaces
              Input streams contain properly formatted client data
              Memory allocation succeeds for new client objects
              Some clients may have only lastName (no firstName)
-----------------------------------------------------------------------------
*/

#include "clientManager.h"
#include <sstream>

using namespace std;


// Default Constructor
// Initializes empty client management system
ClientManager::ClientManager() {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up all client management resources
// Hash table destructor handles all cleanup automatically
ClientManager::~ClientManager() {
    
}

// ----------------------------------------------------------------------------
// insert
// Inserts existing client object into hash table
// Client added if not duplicate, returns insertion success
bool ClientManager::insert(Client* client) {
    return hashTable.insert(client);
}

// ----------------------------------------------------------------------------
// retrieve
// Finds client by ID using hash table lookup
// Client points to found Client or nullptr, returns success status
bool ClientManager::retrieve(int id, Client*& client) const {
    return hashTable.retrieve(id, client);
}

// ----------------------------------------------------------------------------
// getClient
// Alternative interface for client retrieval
// found points to matching Client or nullptr, returns success
bool ClientManager::getClient(int id, Client*& found) const {
    return hashTable.retrieve(id, found);
}

// ----------------------------------------------------------------------------
// addClient
// Creates new client from parsed string data and adds to system
// New client created and inserted, returns success status
bool ClientManager::addClient(int id, const string& fullName) {
    string lastName, firstName;
    
    // Parse the fullName string (format: "lastName firstName")
    if (!parseClientData(fullName, lastName, firstName)) {
        return false;
    }

    // Create new client object
    Client* client = new Client(id, firstName, lastName);
    
    // Insert into hash table
    if (hashTable.insert(client)) {
        return true;
    } else {
        // Insert failed (probably duplicate), clean up
        delete client;
        return false;
    }
}

// ----------------------------------------------------------------------------
// readClientsFromStream
// All valid clients read and added, returns number successfully added
int ClientManager::readClientsFromStream(istream& input) {
    int clientsAdded = 0;
    string line;

    // Read line by line to handle cases where some clients have only one name
    while (getline(input, line)) {
        if (line.empty()) continue;
        
        istringstream lineStream(line);
        int id;
        string lastName, firstName;
        
        // Read ID and lastName (required)
        if (!(lineStream >> id >> lastName)) {
            continue; // Skip invalid lines
        }
        
        // Try to read firstName (optional)
        lineStream >> firstName; // This might be empty for some clients
        
        // Create new client (firstName might be empty string)
        Client* client = new Client(id, firstName, lastName);
        
        if (hashTable.insert(client)) {
            clientsAdded++;
        } else {
            cout << "ERROR: Failed to add client with ID " << id << " (duplicate)" << endl;
            delete client; // Clean up if insertion failed
        }
    }

    return clientsAdded;
}

// ----------------------------------------------------------------------------
// displayAll
// Shows all clients using hash table display method
// All clients displayed in hash table order
void ClientManager::displayAll() const {
    hashTable.display();
}

// ----------------------------------------------------------------------------
// displayStats
// Shows hash table performance statistics
// Hash table statistics displayed for performance analysis
void ClientManager::displayStats() const {
    hashTable.displayStats();
}

// ----------------------------------------------------------------------------
// clear
// Removes all clients from the management system
// All clients removed and deallocated via hash table clear
void ClientManager::clear() {
    hashTable.clear();
}

// ----------------------------------------------------------------------------
// parseClientData
// Parses fullName string into separate lastName and firstName
// lastName and firstName extracted if parsing successful
bool ClientManager::parseClientData(const string& fullName, string& lastName, string& firstName) const {
    istringstream iss(fullName);
    
    // Parse in format: lastName firstName
    if (!(iss >> lastName >> firstName)) {
        return false;
    }

    // Check if we have both names
    if (lastName.empty() || firstName.empty()) {
        return false;
    }

    return true;
}