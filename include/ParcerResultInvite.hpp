#ifndef PARCERRESULTINVITE_HPP
#define PARCERRESULTINVITE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultInvite : public AParcerResult {
  public:
    ParcerResultInvite();
    ParcerResultInvite(const ParcerResultInvite &other);
    ParcerResultInvite& operator=(const ParcerResultInvite& other);
    ~ParcerResultInvite();
    //TODO
    //bool isAllowedChar(char usernameChar);
    //int checkInviteParams(std::vector<std::string> messageVec);
    
    void setParams(std::vector<std::string> inviteCommand);
    const std::vector<std::string> getInviteParams(void) const;
    void printResult() const;
  private:
    std::vector <std::string> _inviteParamsVec;
};

#endif