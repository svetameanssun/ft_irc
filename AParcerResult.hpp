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
    AParcerResult&operator=(const AParcerResult& other);
    virtual ~AParcerResult() {};
    std::string getCommand()const;
    
  protected:
    std::string _command;

};


#endif
