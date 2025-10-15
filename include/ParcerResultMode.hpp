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
    
    //void setUserParams(std::vector<std::string> userCommand);
    void setParams(std::vector<std::string> modeCommand);
    const std::vector<std::string> getModeParams(void) const;
    void printResult() const;
    //bool isAllowedChar(char usernameChar);
    int checkModeParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _topicParamsVec;
};

#endif