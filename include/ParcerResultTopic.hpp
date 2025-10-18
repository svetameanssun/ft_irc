#ifndef PARCERRESULTTOPIC_HPP
#define PARCERRESULTTOPIC_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultTopic : public AParcerResult {
  public:
    ParcerResultTopic();
    ParcerResultTopic(const ParcerResultTopic &other);
    ParcerResultTopic& operator=(const ParcerResultTopic& other);
    ~ParcerResultTopic();
    
    //void setUserParams(std::vector<std::string> userCommand);
    void setParams(std::vector<std::string> topicCommand);
    const std::vector<std::string> getTopicParams(void) const;
    void printResult() const;
    //bool isAllowedChar(char usernameChar);
    int checkTopicParams(std::vector<std::string> messageVec);
  private:
    std::vector <std::string> _topicParamsVec;
};

#endif
