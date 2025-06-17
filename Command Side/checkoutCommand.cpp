/*
-----------------------------------------------------------------------------
 File: checkoutCommand.cpp
 Description: Implementation of CheckoutCommand class. Handles checking out
              publications to clients with proper error handling, copy
              management, and client name resolution for error messages.
 Author: Sharjeel Khan
 Assumptions: Publications exist in MediaContainer
              Clients exist in ClientManager

              Only 'H' (hard copy) format is supported
-----------------------------------------------------------------------------
*/

#include "checkoutCommand.h"
#include "client.h"
#include "fiction.h"
#include "children.h"
#include "periodical.h"
#include <sstream>

// Constants
const int INVALID_CLIENT_ID = -1;
const char VALID_FORMAT = 'H'; // Hard copy format

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes checkout command with invalid values
// CheckoutCommand created with default state
CheckoutCommand::CheckoutCommand() 
    : clientID(INVALID_CLIENT_ID), publicationType('\0'), formatType('\0'), publicationData("") {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up checkout command resources
// CheckoutCommand properly destroyed
CheckoutCommand::~CheckoutCommand() {
}

// ----------------------------------------------------------------------------
// execute
// Executes checkout command for specified client and publication
// Publication checked out if available, client history updated
bool CheckoutCommand::execute(MediaContainer& publications, ClientManager& clients) {
    // Validate client ID
    if (clientID == INVALID_CLIENT_ID) {
        setError("Invalid client ID for checkout command");
        return false;
    }

    // Find the client
    Client* client = nullptr;
    if (!clients.getClient(clientID, client) || client == nullptr) {
        setError("There is no client with ID " + to_string(clientID) + ".");
        return false;
    }

    // Validate format type
    if (formatType != VALID_FORMAT) {
        setError("Invalid format type '" + string(1, formatType) + "'. Only 'H' (hard copy) is supported.");
        return false;
    }

    // Create target publication for searching
    Media* targetPub = createTargetPublication();
    if (!targetPub) {
        setError("Invalid publication type '" + string(1, publicationType) + "'.");
        return false;
    }

    // Find the publication in library
    Media* foundPub = publications.retrieve(*targetPub, publicationType);
    delete targetPub; // Clean up search target
    
    if (!foundPub) {
        setError(client->getFirstName() + " " + client->getLastName() + 
                 " tried to check out '" + extractTitle() + "' - not found in catalog.");
        return false;
    }

    // Check if copies are available
    if (foundPub->getCopies() <= 0) {
        setError(client->getFirstName() + " " + client->getLastName() + 
                 " tried to check out '" + extractTitle() + "' - no copies available.");
        return false;
    }

    // Perform checkout - decrease available copies
    Publication* pub = dynamic_cast<Publication*>(foundPub);
    if (pub) {
        pub->decreaseCopies();
        return true;
    }

    setError("Internal error: Could not process checkout");
    return false;
}

// ----------------------------------------------------------------------------
// setData
// Sets command data from string format "C clientID type format data"
// All checkout parameters extracted and stored
bool CheckoutCommand::setData(const string& data) {
    istringstream iss(data);
    char commandCode;
    
    // Parse command: C clientID type format publicationData
    if (!(iss >> commandCode >> clientID >> publicationType >> formatType)) {
        setError("Invalid format for checkout command");
        return false;
    }

    if (commandCode != 'C') {
        setError("Invalid command code for checkout command");
        return false;
    }

    if (clientID < 1000 || clientID > 9999) {
        setError("Invalid client ID: must be 4-digit number");
        return false;
    }

    // Get remaining data as publication information
    getline(iss >> ws, publicationData);

    errorMessage = "";  // Clear any previous errors
    return true;
}

// ----------------------------------------------------------------------------
// create
// Factory method to create new CheckoutCommand instance
// Returns pointer to new CheckoutCommand object
Command* CheckoutCommand::create() {
    return new CheckoutCommand();
}

// ----------------------------------------------------------------------------
// createTargetPublication
// Creates temporary publication object for searching
// Returns new publication object or nullptr for invalid type
Media* CheckoutCommand::createTargetPublication() const {
    Media* target = nullptr;
    
    switch (publicationType) {
        case 'F':
            target = new Fiction();
            break;
        case 'C':
            target = new Children();
            break;
        case 'P':
            target = new Periodical();
            break;
        default:
            return nullptr;
    }
    
    // Parse publication data into target object
    // Need to convert command format to data file format
    istringstream dataStream;
    string convertedData;
    
    if (publicationType == 'P') {
        // Command: "year month title,"
        // Data file: "title, month year"
        istringstream cmdStream(publicationData);
        int year, month;
        string title;
        cmdStream >> year >> month;
        getline(cmdStream >> ws, title, ',');
        
        convertedData = title + ", " + to_string(month) + " " + to_string(year);
    } else if (publicationType == 'C') {
        // Command: "title, author,"
        // Data file: "author, title, year"
        istringstream cmdStream(publicationData);
        string title, author;
        getline(cmdStream, title, ',');
        getline(cmdStream >> ws, author, ',');
        
        convertedData = author + ", " + title + ", 0"; // Year doesn't matter for searching
    } else {
        // Fiction: command format matches data file format
        convertedData = publicationData;
    }
    
    dataStream.str(convertedData);
    target->setData(dataStream);
    
    return target;
}

// ----------------------------------------------------------------------------
// extractTitle
// Extracts title from publication data for error messages
// Post: Returns title string for display
string CheckoutCommand::extractTitle() const {
    istringstream iss(publicationData);
    string title;
    
    if (publicationType == 'P') {
        // Periodicals in commands: year month title,
        int year, month;
        iss >> year >> month;
        getline(iss >> ws, title, ',');
    } else if (publicationType == 'C') {
        // Children's in commands: title, author,
        getline(iss, title, ',');
    } else {
        // Fiction in commands: author, title,
        string author;
        getline(iss, author, ',');
        getline(iss >> ws, title, ',');
    }
    
    return title;
}