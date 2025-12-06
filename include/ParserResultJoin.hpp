#ifndef PARSERRESULTJOIN_HPP
#define PARSERRESULTJOIN_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultJoin : public AParserResult {
  public:
    ParserResultJoin();
    ParserResultJoin(const ParserResultJoin &other);
    ParserResultJoin& operator=(const ParserResultJoin& other);
    ~ParserResultJoin();
  
    const std::vector<std::string> stringToVec(std::string string, char devisor);
    //const std::map<std::string, std::string> stringsToMap(std::string keyString, std::string valueString);
    
    int checkJoinParamas(std::vector <std::string> messageVector);
    void setParams(std::vector<std::string> joinCommand);

    const std::vector <std::string> getJoinParamsVec(void) const;
    const std::vector <std::string> getJoinChannelsVec(void) const;
    const std::vector <std::string> getJoinPasswordsVec(void) const;
    const bool getLeaveAllChansFlag(void) const;
    void printResult() const;
  private:
    std::vector <std::string> _joinParamsVec;
    //std::map<std::string, std::string> _channelPasswordMap;
    std::vector <std::string> _joinChannelsVec;
    std::vector <std::string> _joinPasswordsVec;
    bool leaveAllChans; // if the flag is TRUE -> the server has to remove the client from ALL the channels!
};

#endif
