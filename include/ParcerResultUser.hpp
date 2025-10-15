#ifndef PARCERRESULTUSER_HPP
#define PARCERRESULTUSER_HPP

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
    bool isAllowedChar(char usernameChar);
    int checkUserParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _userParamsVec;
    std::string _userName;
};

#endif
