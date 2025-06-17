/*
 -----------------------------------------------------------------------------
 File: checkoutCommand.h
 Description: Checkout command implementation for checking out publications
              to library clients. Handles copy management and client-publication
              association tracking.
 Author: Sharjeel Khan
 Assumptions: MediaContainer can retrieve publications by type and data
              ClientManager can find clients by ID
              Command data format is "C clientID type format publicationData"
 -----------------------------------------------------------------------------
*/

#ifndef CHECKOUT_COMMAND_H
#define CHECKOUT_COMMAND_H

#include "command.h"
#include "mediaContainer.h"
#include "clientManager.h"

class CheckoutCommand : public Command {
public:

    // Creates checkout command object
    CheckoutCommand();
    

    // Cleans up checkout command resources
    virtual ~CheckoutCommand();

    // Executes checkout command for specified client and publication
    virtual bool execute(MediaContainer& publications, ClientManager& clients) override;

    // Sets command data from string format "C clientID type format data"
    virtual bool setData(const string& data) override;
    
    // Factory method to create new CheckoutCommand instance
    static Command* create();

private:
    int clientID;                     // ID of client checking out publication
    char publicationType;             // Type of publication ('F', 'C', 'P')
    char formatType;                  // Format type ('H' for hard copy)
    string publicationData;           // Publication identification data


    // Creates temporary publication object for searching
    Media* createTargetPublication() const;
    
    // Extracts title from publication data for error messages
    string extractTitle() const;
};

#endif // CHECKOUT_COMMAND_H