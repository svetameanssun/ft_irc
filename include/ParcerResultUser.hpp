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
    
    void setParams(std::vector<std::string> userCommand);
    const std::vector<std::string> getUserParams(void) const;
    const std::string getRealname(void) const;
    const std::string getNickname(void) const;

    void printResult() const;
    bool isAllowedChar(char realnameChar);
    int checkUserParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _userParamsVec;
    std::string _realname;
    std::string _nickname;
};

#endif
