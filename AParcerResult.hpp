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
    explicit AParcerResult(const std::string& command);
    AParcerResult(const AParcerResult &other);
    AParcerResult& operator=(const AParcerResult& other);

    // Polymorphic base class → virtual destructor
    virtual ~AParcerResult() {}

    // Common interface
    std::string getCommand() const;

    // Pure virtual methods to be implemented in derived classes
    virtual void printVec() const = 0;
    virtual void printMap() const;

  protected:
    std::string _command;
};

#endif
