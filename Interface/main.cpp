/*
-----------------------------------------------------------------------------
 File: main.cpp  
 Description: Simple main program for SHHH Library Management System. 
              Handles only I/O operations.Reading data files and processing
              commands through the Library manager class.
 Author: Sharjeel Khan
 Assumptions: Data files exist and are properly formatted
              Library class handles all business logic and error handling
-----------------------------------------------------------------------------
*/

#include "library.h"
#include <iostream>

using namespace std;

// Data file for the SHHH 
const string PUBLICATIONS_FILE = "data4pubs.txt";
const string CLIENTS_FILE = "data4clients.txt";
const string COMMANDS_FILE = "data4commands.txt";


int main() {
    // Create library system
    Library shhh;
    
    // Initialize library with data files
    if (!shhh.initialize(PUBLICATIONS_FILE, CLIENTS_FILE)) {
        return 1; // Library handles error messages
    }
    
    // Process commands from file
    shhh.processCommands(COMMANDS_FILE);
    
    return 0;
}