#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

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


class CommandParser {
  public:
    CommandParser(const std::string &message): _message(message) {};
    CommandParser(const CommandParser&other);
    CommandParser&operator=(const CommandParser&other);
    ~CommandParser();

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
 * @brief parses and analizes the command and its params.
 *
 * This function initiates parsing, analizes the command and parameter
 * structure, and passes the data to the server.
 *
 * @param NOW void
 *		LATER Parser &parser, to init Parser class outside
 * @returns RPL/0 on  success or l ERR (from Replies.hpp)
 */

#endif
