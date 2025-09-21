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
    ~ParcerResultJoin();
    cosnt std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
    cosnt std::vector<std::string> stringToVec(std::string string, char devisor);
    void setChannelNamePassMap(std::map<std::string, std::string> joinResMap);
    void setChannelnameVec(std::vector <std::string> joinResVec);
    cosnt std::map<std::string, std::string> getChannelNamePassMap(void) const;
    const std::vector <std::string> getChannelNameVec(void) const;
  private:
    std::map<std::string, std::string> _channelNamePassMap;
    std::vector <std::string> _channelNameVec;
};

#endif
