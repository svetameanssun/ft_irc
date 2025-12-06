#ifndef PARSERRESULTMODE_HPP
#define PARSERRESULTMODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultMode : public AParserResult {
  public:
    ParserResultMode();
    ParserResultMode(const ParserResultMode &other);
    ParserResultMode& operator=(const ParserResultMode& other);
    ~ParserResultMode();
    
    void setParams(std::vector<std::string> modeCommand);
    const std::vector<std::string> getModeParams(void) const;
    void printResult() const;
    //bool isValidChanFlag(std::string channelFlag);
    //bool isValidChanName(std::string channelName);
    //bool isValidChanNameChar(int c);
    //bool isValidChanParams(std::vector<std::string> messageVec);
    //int checkModeParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _modeParamsVec;
};

#endif

