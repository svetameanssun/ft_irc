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
    const std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
  
    const std::vector<std::string> stringToVec(std::string string, char devisor);
    bool isValidJoin(std::vector <std::string> messageVector);
    void setChannelNamePassMap(std::map<std::string, std::string> joinResMap);
    void setChannelNameVec(std::vector <std::string> joinResVec);
  
    const std::map<std::string, std::string> getChannelNamePassMap(void) const;
    const std::vector <std::string> getChannelNameVec(void) const;
  private:
    std::map<std::string, std::string> _joinResMap;
    std::vector <std::string> _joinResVec;
};

#endif
