#ifndef PARCERRESULTUSER_HPP
#define PARCERRESULTUSR_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultUser : public AParcerResult {
  public:
    ParcerResultUser();
    ParcerResultUser(const ParcerResultUser &other);
    ParcerResultUser& operator=(const ParcerResultUser& other);
    ~ParcerResultUser();
    
    //void setUserParams(std::vector<std::string> userCommand);
    void setParams(std::vector<std::string> userCommand);
    const std::vector<std::string> getUserParams(void) const;
    void printResult() const;
    bool isProhibitedUserChar(char usernameChar);
    int wrongUserParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _userParamsVec;
};

#endif
