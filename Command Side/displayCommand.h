// -----------------------------------------------------------------------------
// File: displayCommand.h
// Description: Display command implementation for showing library contents.
//              Displays all publications sorted by category (Fiction, Children's,
//              Periodicals) with availability information.
// Author: Sharjeel Khan
// Assumptions: MediaContainer has displayAll method for each publication type
//              Display format matches assignment requirements
//              Command data is empty (no parameters needed)
// -----------------------------------------------------------------------------

#ifndef DISPLAY_COMMAND_H
#define DISPLAY_COMMAND_H

#include "command.h"
#include "mediaContainer.h"
#include "clientManager.h"

class DisplayCommand : public Command {
public:
   
    
    // Creates display command object
    DisplayCommand();
    
    // Cleans up display command resources
    virtual ~DisplayCommand();


    // Executes display command showing all library publications
    virtual bool execute(MediaContainer& publications, ClientManager& clients) override;
    

    // Sets command data (display command needs no additional data)
    virtual bool setData(const string& data) override;

    // Factory method to create new DisplayCommand instance
    static Command* create();
};

#endif // DISPLAY_COMMAND_H