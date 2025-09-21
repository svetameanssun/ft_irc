#ifndef APARCERRESULT_HPP
#define APARCERRESULT_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>


class AParcerResult {
  public:
    AParcerResult();
    AParcerResult(const AParcerResult &other);
    AParcerResult&operator=(const AParcerResult& other);
    ~AParcerResult();
    cosnt std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
    cosnt std::vector<std::string> stringToVec(std::string string, char devisor);
  protected:
    std::string _command;

};


#endif
