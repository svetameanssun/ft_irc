#ifndef PARCERRESULTJOIN_HPP
#define PARCERRESULTJOIN_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultJoin : public AParcerResult {
  public:
    ParcerResultJoin();
    ParcerResultJoin(const ParcerResultJoin &other);
    ParcerResultJoin& operator=(const ParcerResultJoin& other);
    ~ParcerResultJoin();
    /*void setChannelNamePassMap(std::map<std::string, std::string> joinResMap);
    void setChannelNameVec(std::vector <std::string> joinResVec);*/
  
    const std::vector<std::string> stringToVec(std::string string, char devisor);
    const std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
    
    bool isValidJoin(std::vector <std::string> messageVector);
    bool isValidChanName(std::string channelName);
    bool isValidChanNameChar(int c);
    void setParams(std::vector<std::string> joinCommand);

    const std::map<std::string, std::string> getJoinParamsMap(void) const;
    const std::vector <std::string> getJoinParamsVec(void) const;
    void printResult() const;
  private:
    std::map<std::string, std::string> _joinParamsMap;
    std::vector <std::string> _joinParamsVec;
};

#endif