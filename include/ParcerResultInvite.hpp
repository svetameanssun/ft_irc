#ifndef PARCERRESULTINVITE_HPP
#define PARCERRESULTINVITE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultInvite : public AParcerResult {
  public:
  /*================= CANONICAL FORM =================*/
    ParcerResultInvite();
    ParcerResultInvite(const ParcerResultInvite &other);
    ParcerResultInvite& operator=(const ParcerResultInvite& other);
    ~ParcerResultInvite();
    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> inviteCommand);
    const std::vector<std::string> getInviteParams(void) const;
    /*================= VALIDATION ======================*/

    //bool isAllowedChar(char usernameChar);
    int checkInviteParams(std::vector<std::string> messageVec);

    /*================== PRINTING =======================*/
    void printResult() const;
  private:
    std::vector <std::string> _inviteParamsVec;
};

#endif
