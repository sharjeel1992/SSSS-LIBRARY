/*
 -----------------------------------------------------------------------------
 File: client.cpp
 Description: Implementation of Client class. Manages client information
              including ID, first name, and last name with comparison
              operations for data structure usage.
 Author: Sharjeel Khan
 Assumptions: Client IDs are unique and used for comparison/hashing
              Data format is "ID lastName firstName" with spaces between fields
 -----------------------------------------------------------------------------
*/
#include "client.h"
#include <iomanip>

using namespace std;

// Constants
const int DEFAULT_ID = 0;
const int ID_DISPLAY_WIDTH = 4;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes client with default values
Client::Client() : id(DEFAULT_ID), firstName(""), lastName("") {
}

// ----------------------------------------------------------------------------
// Parameterized Constructor  
// Creates client with specified ID and names
Client::Client(int id, const string& first, const string& last)
    : id(id), firstName(first), lastName(last) {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up client object resources
Client::~Client() {
}

// ----------------------------------------------------------------------------
// getID
// Returns the client's unique identifier
int Client::getID() const {
    return id;
}

// ----------------------------------------------------------------------------
// getFirstName
// Returns the client's first name
// Pre: Object is properly initialized
// Post: Returns current first name string (may be empty)
string Client::getFirstName() const {
    return firstName;
}

// ----------------------------------------------------------------------------
// getLastName
// Returns the client's last name incase client doesn't have first name
string Client::getLastName() const {
    return lastName;
}

// ----------------------------------------------------------------------------
// setData
// Sets all client information at once,updates cleint data with new values
void Client::setData(int id, const string& first, const string& last) {
    this->id = id;
    this->firstName = first;
    this->lastName = last;
}

// ----------------------------------------------------------------------------
// operator<
// Compares clients by ID for sorting purposes.
// Returns true if this client's ID is numerically less than other's
bool Client::operator<(const Client& other) const {
    return this->id < other.id;
}

// ----------------------------------------------------------------------------
// operator==
// Compares clients for equality based on ID
// Returns true if both clients have identical IDs
bool Client::operator==(const Client& other) const {
    return this->id == other.id;
}

// ----------------------------------------------------------------------------
// display
// Outputs client information in assignment-specified format
// Client data displayed as "ID lastName, firstName" or "ID lastName"
void Client::display() const {
    cout << setw(ID_DISPLAY_WIDTH) << id << " ";
    if (firstName.empty()) {
        cout << lastName << endl;
    } else {
        cout << lastName << ", " << firstName << endl;
    }
}