#ifndef APARCERRESULT_HPP
#define APARCERRESULT_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "Replies.hpp"

class AParcerResult {
  public:
    AParcerResult();
    AParcerResult(std::string command);
    AParcerResult(const AParcerResult &other);
    AParcerResult& operator=(const AParcerResult& other);

    // Polymorphic base class → virtual destructor
    virtual ~AParcerResult() {}

    // Common interface
    std::string getCommand() const;

    // Pure virtual methods to be implemented in derived classes
    virtual void printResult() const = 0;

    virtual void setParams(std::vector<std::string> commandMessage) = 0;

  protected:
    std::string _command;
};

#endif
