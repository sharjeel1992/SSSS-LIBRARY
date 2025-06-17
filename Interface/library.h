/*
 -----------------------------------------------------------------------------
 File: library.h
 Description: SHHH (Stocking Hardy Harmonious Hard copies) Library Manager.
              Main controller class that coordinates all library subsystems
              including publications, clients, and command processing.
              Handles file I/O, system initialization, and main program flow.
 Author: Sharjeel Khan
 Assumptions: Data files are properly formatted.File paths are accessible and readable
              System has sufficient memory for library operations
 -----------------------------------------------------------------------------
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include "mediaContainer.h"
#include "clientManager.h"
#include "commandFactory.h"
#include "publicationFactory.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Library {
public:
    
    // Default Constructor
    Library();
    
  
    // Destructor
    ~Library();
    
    // Loads library data from files and prepares system for operation
    bool initialize(const string& publicationFile, const string& clientFile);
    
    // Processes library commands from file
    int processCommands(const string& commandFile);

    // Processes library commands from input stream
    int processCommandsFromStream(istream& input);
    
    // Shows complete library status (all publications)
    void displayLibrary() const;
    
    // Shows all registered library clients
    void displayClients() const;
    
    // Shows library system statistics
    void displayStatistics() const;
    
    // Checks if library system is ready for operation
    bool isInitialized() const;

private:
    MediaContainer publications;      // Publication management system
    ClientManager clients;            // Client management system  
    CommandFactory factory;           // Command creation and processing system
    PublicationFactory pubFactory;    // Factory for creating publications
    bool initialized;                 // Initialization status flag
    
    // Statistics tracking
    int totalPublications;            // Total publications in library
    int totalClients;                 // Total registered clients
    int totalCommandsProcessed;       // Total commands processed in session

    // Loads publication data from file into library system
    int loadPublications(const string& filename);
    

    // Loads client data from file into library system
    int loadClients(const string& filename);
   
    // Shows welcome message and library information
    void displayWelcome() const;

    // Resets all statistical counters
    void resetStatistics();
};

#endif // LIBRARY_H