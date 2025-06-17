// -----------------------------------------------------------------------------
// File: commandFactory.h
// Description: Command factory for creating and processing library commands.
//              Combines factory creation and command execution in one class
//              for simplified command handling.
// Author: Sharjeel Khan
// Assumptions: All command classes have static create() methods
//              MediaContainer and ClientManager are properly initialized
//              Command data comes from properly formatted input streams
// -----------------------------------------------------------------------------

#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include "command.h"
#include "mediaContainer.h"
#include "clientManager.h"
#include <iostream>
#include <string>

using namespace std;

class CommandFactory {
public:
    // Creates command factory ready to create and process commands
    CommandFactory();

    // Cleans up command factory resources
    ~CommandFactory();

    // Creates appropriate command object based on command type code
    Command* createCommand(char commandType, const string& commandData) const;

    // Creates command object and extracts type from command data string
    Command* createCommand(const string& commandData) const;


    // Creates and executes a single command from string data
    bool processCommand(const string& commandData, MediaContainer& publications, ClientManager& clients) const;

    // Processes multiple commands from input stream
    int processCommands(istream& input, MediaContainer& publications, ClientManager& clients) const;

private:

    // Checks if command type character is supported
    bool isValidCommandType(char commandType) const;
};

#endif // COMMAND_FACTORY_H