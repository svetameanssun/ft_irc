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
    explicit AParcerResult(const std::string& command); //prevents the compiler to use the implicit covvertions.
    // does it even work in c++98??
    AParcerResult(const AParcerResult &other);
    AParcerResult& operator=(const AParcerResult& other);

    // Polymorphic base class → virtual destructor
    virtual ~AParcerResult() {}

    // Common interface
    std::string getCommand() const;

    // Pure virtual method to be implemented in derived classes
    virtual void printResult() const = 0;

  protected:
    std::string _command;
};

#endif
