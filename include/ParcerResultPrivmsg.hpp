#ifndef PARCERRESULTPRIVMSG_HPP
#define PARCERRESULTPRIVMSG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultPrivmsg : public AParcerPrivmsg {
  public:
    ParcerResultPrivmsg();
    ParcerResultPrivmsg(const ParcerResultPrivmsg &other);
    ParcerResultPrivmsg& operator=(const ParcerResultPrivmsg& other);
    ~ParcerResultPrivmsg();
    
    void setParams(std::vector<std::string> privmsgCommand);
    const std::vector<std::string> getPrivmsgParams(void) const;
    void printResult() const;
    //bool isAllowedChar(char usernameChar);
    int checkPrivmsgParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _privmsgParamsVec;
};

#endif