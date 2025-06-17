/*
 -----------------------------------------------------------------------------
 File: library.cpp
 Description: Implementation of SHHH Library Manager. Coordinates all library
              subsystems, handles file I/O, and provides main program interface
              for the complete library management system.
 Author: Sharjeel Khan
 Assumptions: System has adequate resources for library operations
              File I/O operations may fail and should be handled gracefully
 -----------------------------------------------------------------------------
*/

#include "library.h"
#include <sstream>
#include <iomanip>

// Constants
const int INITIAL_COUNT = 0;

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes empty library system with all subsystems
Library::Library() : initialized(false) {
    resetStatistics();
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up all library resources
Library::~Library() {
    // All objects are automatic - no manual cleanup needed
}

// ----------------------------------------------------------------------------
// Initialize
// Loads library data from files and sets up complete system
bool Library::initialize(const string& publicationFile, const string& clientFile) {
    cout << "Initializing SHHH Library System..." << endl;
    cout << "====================================" << endl << endl;

    resetStatistics();

    // Load publications first
    cout << "Loading publications from: " << publicationFile << endl;
    totalPublications = loadPublications(publicationFile);
    if (totalPublications == 0) {
        cout << "ERROR: No publications loaded. Check file: " << publicationFile << endl;
        return false;
    }
    cout << "Successfully loaded " << totalPublications << " publications." << endl << endl;

    // Load clients
    cout << "Loading clients from: " << clientFile << endl;
    totalClients = loadClients(clientFile);
    if (totalClients == 0) {
        cout << "ERROR: No clients loaded. Check file: " << clientFile << endl;
        return false;
    }
    cout << "Successfully loaded " << totalClients << " clients." << endl << endl;

    initialized = true;
    displayWelcome();
    return true;
}

// ----------------------------------------------------------------------------
// ProcessCommands
// Processes commands from specified file
int Library::processCommands(const string& commandFile) {
    if (!initialized) {
        cout << "ERROR: Library not initialized. Call initialize() first." << endl;
        return 0;
    }

    ifstream commandStream(commandFile);
    if (!commandStream.is_open()) {
        cout << "ERROR: Cannot open command file: " << commandFile << endl;
        return 0;
    }

    cout << "\nProcessing commands from: " << commandFile << endl;
    cout << "==========================================" << endl;

    int commandsProcessed = processCommandsFromStream(commandStream);
    commandStream.close();

    totalCommandsProcessed += commandsProcessed;
    return commandsProcessed;
}

// ----------------------------------------------------------------------------
// processCommandsFromStream
// Processes commands from input stream
int Library::processCommandsFromStream(istream& input) {
    if (!initialized) {
        cout << "ERROR: Library not properly initialized." << endl;
        return 0;
    }
    return factory.processCommands(input, publications, clients);
}

// ----------------------------------------------------------------------------
// displayLibrary
// Shows complete library status with all publications
void Library::displayLibrary() const {
    if (!initialized) {
        cout << "ERROR: Library not initialized." << endl;
        return;
    }

    cout << "\n" << string(60, '=') << endl;
    cout << "SHHH LIBRARY COMPLETE CATALOG" << endl;
    cout << string(60, '=') << endl;

    publications.displayAll('F');
    publications.displayAll('C');
    publications.displayAll('P');
}

// ----------------------------------------------------------------------------
// DisplayClients
// Shows all registered library clients

void Library::displayClients() const {
    if (!initialized) {
        cout << "ERROR: Library not initialized." << endl;
        return;
    }

    cout << "\n" << string(40, '=') << endl;
    cout << "SHHH LIBRARY REGISTERED CLIENTS" << endl;
    cout << string(40, '=') << endl;
    clients.displayAll();
}

// ----------------------------------------------------------------------------
// displayStatistics
// Shows comprehensive library system statistics
void Library::displayStatistics() const {
    if (!initialized) {
        cout << "ERROR: Library not initialized." << endl;
        return;
    }
    cout << "\n" << string(50, '=') << endl;
    cout << "SHHH LIBRARY SYSTEM STATISTICS" << endl;
    cout << string(50, '=') << endl;
    cout << "Total Publications: " << totalPublications << endl;
    cout << "Total Clients: " << totalClients << endl;
    cout << "Commands Processed This Session: " << totalCommandsProcessed << endl;
    
    cout << "\nClient Management Statistics:" << endl;
    clients.displayStats();
}

// ----------------------------------------------------------------------------
// isInitialized
// Checks library initialization status
bool Library::isInitialized() const {
    return initialized;
}

// ----------------------------------------------------------------------------
// loadPublications
// Loads publication data from file using PublicationFactory
int Library::loadPublications(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot open publication file: " << filename << endl;
        return 0;
    }
    int publicationsLoaded = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        char publicationType = line[0];
        string publicationData = line.substr(2); // Skip type and space

        // Create publication using factory
        Media* publication = pubFactory.createPublication(publicationType);
        if (publication) {
            // Parse publication data
            istringstream dataStream(publicationData);
            publication->setData(dataStream);

            // Insert into library
            if (publications.insert(publication)) {
                publicationsLoaded++;
            } else {
                // Insert failed (duplicate), clean up
                delete publication;
            }
        }
    }

    file.close();
    return publicationsLoaded;
}

// ----------------------------------------------------------------------------
// loadClients
// Loads client data from file using ClientManager
int Library::loadClients(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot open client file: " << filename << endl;
        return 0;
    }
    int clientsLoaded = clients.readClientsFromStream(file);
    file.close();
    return clientsLoaded;
}

// ----------------------------------------------------------------------------
// displayWelcome
// Shows welcome message and basic library information
void Library::displayWelcome() const {
    cout << string(60, '=') << endl;
    cout << "  WELCOME TO SHHH LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "  (Stocking Hardy Harmonious Hard copies)" << endl;
    cout << string(60, '=') << endl;
    cout << "Library successfully initialized!" << endl;
    cout << "Publications loaded: " << totalPublications << endl;
    cout << "Clients registered: " << totalClients << endl;
    cout << "System ready for command processing." << endl;
    cout << string(60, '=') << endl << endl;
}

// ----------------------------------------------------------------------------
// resetStatistics
// Resets all statistical counters to initial values
void Library::resetStatistics() {
    totalPublications = INITIAL_COUNT;
    totalClients = INITIAL_COUNT;
    totalCommandsProcessed = INITIAL_COUNT;
}