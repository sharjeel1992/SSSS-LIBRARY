// -----------------------------------------------------------------------------
// File: command.h
// Description: Abstract base class for all library commands. Implements
//              Command design pattern to support extensible command processing
//              following Open-Close principle for easy addition of new commands.
// Author: Sharjeel Khan
// Assumptions: All commands operate on library data (publications and clients)
//              Commands may succeed or fail and should report their status
//              Command data is parsed from string format
// -----------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>

using namespace std;

// Forward declarations
class MediaContainer;
class ClientManager;

class Command {
public:

    // Creates base command object
    Command();

    // Ensures proper cleanup of derived command classes
    virtual ~Command();


    // Pure virtual method to execute the command
    virtual bool execute(MediaContainer& publications, ClientManager& clients) = 0;
    
 
    // Pure virtual method to set command data from string
    virtual bool setData(const string& data) = 0;
    
  
    // Returns error message if command execution failed
    virtual string getErrorMessage() const;

protected:
    string errorMessage;           // Stores error message for failed commands
    
   
    // Helper method to set error message
    void setError(const string& message);
};

#endif // COMMAND_H