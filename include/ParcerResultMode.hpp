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
