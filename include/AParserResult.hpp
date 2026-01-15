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
    // default-check hooks used by CommandDispatcher; overridden where needed
    virtual int checkUserParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkJoinParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkPartParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkTopicParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkInviteParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkKickParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkPrivmsgParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual int checkNoticeParams(std::vector<std::string> /*messageVec*/) { return 0; }
    virtual void collectQuitMessage(std::vector<std::string> &/*messageVec*/) {}

    
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