#ifndef PARCERRESULTKICK_HPP
#define PARCERRESULTKICK_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultKick : public AParcerResult {
  public:
    ParcerResultKick();
    ParcerResultKick(const ParcerResultKick &other);
    ParcerResultKick& operator=(const ParcerResultKick& other);
    ~ParcerResultKick();
    
    void setParams(std::vector<std::string> kickCommand);
    const std::vector<std::string> getKickParams(void) const;
    void printResult() const;
    //bool isAllowedChar(char usernameChar);
    int checkKickParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _kickParamsVec;
};

#endif