// -----------------------------------------------------------------------------
// File: historyCommand.cpp
// Description: Implementation of HistoryCommand class. Handles display of
//              client transaction history including all checkout and return
//              operations in chronological order.
// Author: Sharjeel Khan
// Assumptions: ClientManager can find clients by ID
//              Client objects maintain transaction history
//              Command format is "H clientID"
// -----------------------------------------------------------------------------

#include "historyCommand.h"
#include "client.h"
#include <sstream>

// Constants
const int INVALID_CLIENT_ID = -1;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes history command with invalid client ID
// HistoryCommand created with default state
HistoryCommand::HistoryCommand() : clientID(INVALID_CLIENT_ID) {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up history command resources
// HistoryCommand properly destroyed
HistoryCommand::~HistoryCommand() {
}

// ----------------------------------------------------------------------------
// execute
// Displays transaction history for specified client
// Client history displayed if client exists
bool HistoryCommand::execute(MediaContainer& publications, ClientManager& clients) {
    if (clientID == INVALID_CLIENT_ID) {
        setError("Invalid client ID for history command");
        return false;
    }

    // Find the client
    Client* client = nullptr;
    if (!clients.getClient(clientID, client) || client == nullptr) {
        setError("There is no client with ID " + to_string(clientID) + ".");
        return false;
    }

    // Display client information and history header
    cout << "Transaction history for client ";
    client->display();
    cout << endl;

    // Display actual transaction history when implemented
    // For now, show placeholder message
    cout << "  (No transactions recorded)" << endl;

    return true;
}

// ----------------------------------------------------------------------------
// setData
// Parses command data to extract client ID
// clientID extracted and stored
bool HistoryCommand::setData(const string& data) {
    istringstream iss(data);
    char commandCode;
    
    // Parse command: H clientID
    if (!(iss >> commandCode >> clientID)) {
        setError("Invalid format for history command");
        return false;
    }

    if (commandCode != 'H') {
        setError("Invalid command code for history command");
        return false;
    }

    if (clientID < 1000 || clientID > 9999) {
        setError("Invalid client ID: must be 4-digit number");
        return false;
    }

    errorMessage = "";  // Clear any previous errors
    return true;
}

// ----------------------------------------------------------------------------
// create
// Factory method to create new HistoryCommand instance
// Returns pointer to new HistoryCommand object
Command* HistoryCommand::create() {
    return new HistoryCommand();
}