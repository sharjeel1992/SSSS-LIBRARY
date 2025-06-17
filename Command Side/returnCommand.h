/*
-----------------------------------------------------------------------------
 File: returnCommand.h
 Description: Return command implementation for returning publications
              from library clients. Handles copy management and validation
              that items were actually checked out.
 Author: Sharjeel Khan
 Assumptions: MediaContainer can retrieve publications by type and data
              ClientManager can find clients by ID
              Command data format is "R clientID type format publicationData"
-----------------------------------------------------------------------------
*/

#ifndef RETURN_COMMAND_H
#define RETURN_COMMAND_H

#include "command.h"
#include "mediaContainer.h"
#include "clientManager.h"

class ReturnCommand : public Command {
public:
    // Creates return command object
    ReturnCommand();
    
    // Cleans up return command resources
    virtual ~ReturnCommand();

   
    // Executes return command for specified client and publication
    virtual bool execute(MediaContainer& publications, ClientManager& clients) override;

    // Sets command data from string format "R clientID type format data"
    virtual bool setData(const string& data) override;
    
    // Factory method to create new ReturnCommand instance
    static Command* create();

private:
    int clientID;                     // ID of client returning publication
    char publicationType;             // Type of publication ('F', 'C', 'P')
    char formatType;                  // Format type ('H' for hard copy)
    string publicationData;           // Publication identification data

 
    // Creates temporary publication object for searching
    Media* createTargetPublication() const;
    
    // Extracts title from publication data for error messages
    string extractTitle() const;
};

#endif // RETURN_COMMAND_H