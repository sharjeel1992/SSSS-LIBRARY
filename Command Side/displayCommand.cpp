// -----------------------------------------------------------------------------
// File: displayCommand.cpp
// Description: Implementation of DisplayCommand class. Handles display of
//              all library publications organized by category with proper
//              formatting and availability information.
// Author: Sharjeel Khan
// Assumptions: MediaContainer supports displayAll for each publication type
//              Output format matches assignment sample output requirements
// -----------------------------------------------------------------------------

#include "displayCommand.h"


// ----------------------------------------------------------------------------
// Default Constructor
// Initializes display command
// DisplayCommand created and ready for execution
DisplayCommand::DisplayCommand() {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up display command resources
// DisplayCommand properly destroyed
DisplayCommand::~DisplayCommand() {
}

// ----------------------------------------------------------------------------
// execute
// Displays all library publications by category
// All publications displayed in sorted order by category
bool DisplayCommand::execute(MediaContainer& publications, ClientManager& clients) {
    // Display all publication categories
    // Fiction sorted by author, then title
    publications.displayAll('F');
    
    // Children's sorted by title, then author  
    publications.displayAll('C');
    
    // Periodicals sorted by year, then month, then title
    publications.displayAll('P');
    
    return true; // Display command always succeeds
}

// ----------------------------------------------------------------------------
// setData
// Sets command data for display command (no data needed)
// Command is ready for execution
bool DisplayCommand::setData(const string& data) {
    // Display command doesn't need any additional data
    // Just clear any previous error state
    errorMessage = "";
    return true;
}

// ----------------------------------------------------------------------------
// create
// Factory method to create new DisplayCommand instance
// Returns pointer to new DisplayCommand object
Command* DisplayCommand::create() {
    return new DisplayCommand();
}