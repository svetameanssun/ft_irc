#ifndef COMMANDPARCER_HPP
#define COMMANDPARCER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>
#include <map>
#include <algorithm>
#include <cctype>


#include "CommandDispatcher.hpp"

class CommandParcer {
  public:
    CommandParcer(std::string message): _message(message) {};
    CommandParcer(const CommandParcer&other);
    CommandParcer&operator=(const CommandParcer&other);
    ~CommandParcer();

    int splitMessage(void);
    int commandProccess(void);
    std::string getMessage(void) const;
    std::vector<std::string> getMessageVec(void) const;
  private:
    const std::string _message;
    std::vector<std::string> _messageVec;

    CommandDispatcher _cmdDisp;
};
/**
 * @brief parces and analizes the command and its params.
 *
 * This function initiates parcing, analizes the command and parameter
 * structure, and passes the data to the server.
 *
 * @param NOW void
 *		LATER Parcer &parcer, to init Parcer class outside
 * @returns RPL/0 on  success or l ERR (from Replies.hpp)
 */

//TEMPORAL, later this function (or its content) will fit into some part of the server's code
int launchParcing(void);


#endif
