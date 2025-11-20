#ifndef PARCERRESULTPRIVMSG_HPP
#define PARCERRESULTPRIVMSG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultPrivmsg : public AParcerResult {
  public:
    ParcerResultPrivmsg();
    ParcerResultPrivmsg(const ParcerResultPrivmsg &other);
    ParcerResultPrivmsg& operator=(const ParcerResultPrivmsg& other);
    ~ParcerResultPrivmsg();
    
    void setParams(std::vector<std::string> privmsgCommand);
    const std::vector<std::string> getPrivmsgParams(void) const;
    void printResult() const;
    const std::vector<std::string> stringToVec(std::string str, char delim);
    //bool isSpecialChar(int c);
    //bool isValidNick(std::vector<std::string> nickCommand);
    int checkPrivmsgTarget(std::string privmsgTarget);
    int checkPrivmsgParams(std::vector <std::string> messageVector);
  private:
    std::vector <std::string> _targetVec;
    std::vector <std::string> _privmsgParamsVec;
    std::string _privmsgMessage;
};

#endif
