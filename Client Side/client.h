/*
-----------------------------------------------------------------------------
 File: client.h
 Description: Client class representing library patrons. Stores client ID,
              first name, and last name. Supports comparison operations for
              sorting and searching in data structures.
 Author: Sharjeel Khan
 Assumptions: Client IDs are unique 4-digit integers
              Data format is "ID lastName firstName" with spaces between fields
              Some clients may have only lastName (no firstName)
-----------------------------------------------------------------------------
*/
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

using namespace std;

class Client {
public:
    // Default Constructor
    // Creates client with default values (ID=0, empty names)
    Client();
    
    // Parameterized Constructor
    // Creates client with specified ID and names
    Client(int id, const string& firstName, const string& lastName);
    
    // Destructor
    // Cleans up client object resources
    ~Client();

   
    // Accessor methods
    int getID() const;
    string getFirstName() const;
    string getLastName() const;
    

    // setData
    void setData(int id, const string& firstName, const string& lastName);
   
    // Compares clients for sorting by ID
    bool operator<(const Client& other) const;
    
    // Compares clients for equality by ID
    bool operator==(const Client& other) const;

    // Outputs client information in formatted manner
    void display() const;

private:
    int id;                           // Unique 4-digit client identifier
    string firstName;                 // Client's first name (may be empty)
    string lastName;                  // Client's last name
};

#endif // CLIENT_H