// -----------------------------------------------------------------------------
// File: commandFactory.cpp
// Description: Implementation of CommandFactory class. Creates and processes
//              library commands using Factory pattern. Combines creation and
//              execution for simplified command handling.
// Author: Sharjeel Khan
// Assumptions: All command classes have static create() methods
//              Library systems are properly initialized before processing
//              Input streams contain one command per line
// -----------------------------------------------------------------------------

#include "commandFactory.h"
#include "displayCommand.h"
#include "historyCommand.h"
#include "checkoutCommand.h"
#include "returnCommand.h"
#include <sstream>

using namespace std;

// Constants for command types
const char CHECKOUT_COMMAND = 'C';
const char RETURN_COMMAND = 'R';
const char HISTORY_COMMAND = 'H';
const char DISPLAY_COMMAND = 'D';

// ----------------------------------------------------------------------------
// Default Constructor
// Initializes command factory
// CommandFactory ready to create and process commands
CommandFactory::CommandFactory() {
}

// ----------------------------------------------------------------------------
// Destructor
// Cleans up command factory resources
// CommandFactory properly destroyed
CommandFactory::~CommandFactory() {
}

// ----------------------------------------------------------------------------
// createCommand
// Creates command object based on type and initializes with data
// Returns initialized command object or nullptr for invalid type
Command* CommandFactory::createCommand(char commandType, const string& commandData) const {
    Command* command = nullptr;

    // Create appropriate command based on type
    switch (commandType) {
        case CHECKOUT_COMMAND:
            command = CheckoutCommand::create();
            break;
            
        case RETURN_COMMAND:
            command = ReturnCommand::create();
            break;
            
        case HISTORY_COMMAND:
            command = HistoryCommand::create();
            break;
            
        case DISPLAY_COMMAND:
            command = DisplayCommand::create();
            break;
            
        default:
            // Invalid command type
            cout << "ERROR: '" << commandType << "' is not a valid command type." << endl;
            return nullptr;
    }

    // Initialize command with data
    if (command != nullptr) {
        if (!command->setData(commandData)) {
            // Failed to set data - clean up and return nullptr
            cout << "ERROR: " << command->getErrorMessage() << endl;
            delete command;
            return nullptr;
        }
    }

    return command;
}

// ----------------------------------------------------------------------------
// createCommand (overload)
// Creates command object by extracting type from command data string
// Returns initialized command object or nullptr for invalid data
Command* CommandFactory::createCommand(const string& commandData) const {
    if (commandData.empty()) {
        cout << "ERROR: Empty command data." << endl;
        return nullptr;
    }

    char commandType = commandData[0];
    
    if (!isValidCommandType(commandType)) {
        cout << "ERROR: '" << commandType << "' is not a valid command type." << endl;
        return nullptr;
    }

    return createCommand(commandType, commandData);
}

// ----------------------------------------------------------------------------
// processCommand
// Creates and executes a single command from string data
// Command executed if valid, error message displayed if invalid
bool CommandFactory::processCommand(const string& commandData, MediaContainer& publications, ClientManager& clients) const {
    // Skip empty lines
    if (commandData.empty()) {
        return true;
    }

    // Create command using factory
    Command* command = createCommand(commandData);
    if (command == nullptr) {
        return false;
    }

    // Execute the command
    bool success = command->execute(publications, clients);
    
    if (!success) {
        // Display error message for failed commands
        cout << "ERROR: " << command->getErrorMessage() << endl;
    }

    // Clean up command object
    delete command;
    
    return success;
}

// ----------------------------------------------------------------------------
// processCommands
// Processes multiple commands from input stream
// All commands processed
int CommandFactory::processCommands(istream& input, MediaContainer& publications, ClientManager& clients) const {
    string line;
    int successfulCommands = 0;

    // Process each line as a command
    while (getline(input, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        if (processCommand(line, publications, clients)) {
            successfulCommands++;
        }
    }

    return successfulCommands;
}

// ----------------------------------------------------------------------------
// isValidCommandType
// Validates command type character
// Returns true if command type is supported
bool CommandFactory::isValidCommandType(char commandType) const {
    return commandType == CHECKOUT_COMMAND ||
           commandType == RETURN_COMMAND ||
           commandType == HISTORY_COMMAND ||
           commandType == DISPLAY_COMMAND;
}

// ----------------------------------------------------------------------------
// Command Base Class Implementation
// Default Constructor
// Initializes base command with empty error message
// Command object created with no error state
Command::Command() : errorMessage("") {
}

// ----------------------------------------------------------------------------
// Virtual Destructor
// Cleans up base command resources
// Command object properly destroyed
Command::~Command() {
}

// ----------------------------------------------------------------------------
// getErrorMessage
// Returns current error message
// Returns error message string (empty if no error)
string Command::getErrorMessage() const {
    return errorMessage;
}

// ----------------------------------------------------------------------------
// setError
// Sets error message for failed command execution
// errorMessage updated with provided message
void Command::setError(const string& message) {
    errorMessage = message;
}