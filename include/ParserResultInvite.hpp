#ifndef PARSERRESULTINVITE_HPP
#define PARSERRESULTINVITE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultInvite : public AParserResult {
  public:
  /*================= CANONICAL FORM =================*/
    ParserResultInvite();
    ParserResultInvite(const ParserResultInvite &other);
    ParserResultInvite& operator=(const ParserResultInvite& other);
    ~ParserResultInvite();
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