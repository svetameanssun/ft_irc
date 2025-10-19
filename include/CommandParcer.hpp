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
    CommandParcer(const std::string &message): _message(message) {};
    CommandParcer(const CommandParcer&other);
    CommandParcer&operator=(const CommandParcer&other);
    ~CommandParcer();

    bool splitMessage(void);
    int commandProccess(void);
    const std::string &getMessage(void) const;
    const std::vector<std::string> &getMessageVec(void) const;
    const CommandDispatcher & getCommandDispatcher()const ;

  private:
    const std::string &_message;
    std::vector<std::string> _messageVec; // this is the initial vector!

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
//int launchParcing(std::string messageStr);


#endif
