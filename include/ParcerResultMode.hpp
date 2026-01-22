#ifndef PARCERRESULTMODE_HPP
#define PARCERRESULTMODE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultMode : public AParcerResult {
  public:
    ParcerResultMode();
    ParcerResultMode(const ParcerResultMode &other);
    ParcerResultMode& operator=(const ParcerResultMode& other);
    ~ParcerResultMode();
    
    void fillInModeMap();
    void setParams(std::vector<std::string> modeCommand);
    const std::vector<std::string> getModeParams(void) const;
    void printResult() const;

    bool isValidChanName(std::string channelName);
    bool isValidChanNameChar(int c);
  
    int checkModeParams(std::vector<std::string> messageVec);
    void initModeMap(void);
    bool isValidCommandElement(std::string);
  private:
    std::vector <std::string> _modeParamsVec;
    std::map <std::string, std::string> _modeParamsMap;
};

#endif