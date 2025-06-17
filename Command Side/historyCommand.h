// -----------------------------------------------------------------------------
// File: historyCommand.h
// Description: History command implementation for displaying client transaction
//              history. Shows all checkout and return operations for a specific
//              client in chronological order.
// Author: Sharjeel Khan
// Assumptions: ClientManager can retrieve clients by ID
//              Client history tracking is implemented
//              Command data format is "H clientID"
// -----------------------------------------------------------------------------

#ifndef HISTORY_COMMAND_H
#define HISTORY_COMMAND_H

#include "command.h"
#include "mediaContainer.h"
#include "clientManager.h"

class HistoryCommand : public Command {
public:
    // Creates history command object
    HistoryCommand();

    // Cleans up history command resources
    virtual ~HistoryCommand();

 
    // Executes history command showing client transaction history
    virtual bool execute(MediaContainer& publications, ClientManager& clients) override;
    

    // Sets command data from string format "H clientID"
    virtual bool setData(const string& data) override;
    

    // Factory method to create new HistoryCommand instance
    static Command* create();

private:
    int clientID;         // ID of client whose history to display
};

#endif // HISTORY_COMMAND_H