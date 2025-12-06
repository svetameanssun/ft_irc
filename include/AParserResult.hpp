#ifndef APARSERRESULT_HPP
#define APARSERRESULT_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "Replies.hpp"

class AParserResult {
  public:
    AParserResult();
    AParserResult(std::string command);
    AParserResult(const AParserResult &other);
    AParserResult& operator=(const AParserResult& other);

    // Polymorphic base class → pure virtual destructor
    virtual ~AParserResult() = 0;

    // Common getter
    std::string getCommand() const;

    // Virtual methods to be implemented in derived classes
    virtual void printResult() const = 0;
    virtual void setParams(std::vector<std::string> commandMessage) = 0;

    // Methods to validate channel name
    bool isValidChanNameChar(int c);
    bool isValidChanName(std::string channelName);

    // Methods to validade nickname
    bool isSpecialChar(int c);
    bool isValidNick(std::string nickname);

  protected:
    std::string _command;
};

#endif
