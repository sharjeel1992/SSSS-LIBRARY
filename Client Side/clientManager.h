/*
-----------------------------------------------------------------------------
 File: clientManager.h
 Description: Manager class for library clients using custom hash table.
              Provides high-level interface for client operations including
              adding, retrieving, and displaying client information.
              Uses hash table for O(1) average lookup time.
 Author: Sharjeel Khan
 Assumptions: Client data format is "ID lastName firstName" with spaces
              Client IDs are unique 4-digit integers
              Hash table provides O(1) average lookup time
              Some clients may have only lastName (no firstName)
-----------------------------------------------------------------------------
*/

#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "client.h"
#include "clientHash.h"
#include <string>
#include <iostream>

using namespace std;

class ClientManager {
public:
    // Default Constructor
    ClientManager();
    
    // Destructor
    ~ClientManager();

    // Inserts existing client object into management system
    bool insert(Client* client);
    
    // Finds client by ID in the management system
    bool retrieve(int id, Client*& client) const;

    // Alternative interface for client retrieval (same as retrieve)
    bool getClient(int id, Client*& found) const;
    
    // Creates and adds new client from string data
    bool addClient(int id, const string& fullName);
    
    // Reads multiple clients from input stream (for file processing)
    int readClientsFromStream(istream& input);

    // Shows all clients in the management system
    void displayAll() const;

    // Shows hash table performance statistics
    void displayStats() const;
    
    // Removes all clients from management system
    void clear();

private:
    ClientHash hashTable;         // Custom hash table for O(1) client lookup

   
  
    // Parses client data string into lastName and firstName
    bool parseClientData(const string& fullName, string& lastName,
                         string& firstName) const;
};

#endif // CLIENTMANAGER_H