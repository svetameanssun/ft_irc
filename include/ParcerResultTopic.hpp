#ifndef PARCERRESULTTOPIC_HPP
#define PARCERRESULTTOPIC_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultTopic : public AParcerResult {
  public:
  /*================= CANONICAL FORM =================*/
    ParcerResultTopic();
    ParcerResultTopic(const ParcerResultTopic &other);
    ParcerResultTopic& operator=(const ParcerResultTopic& other);
    ~ParcerResultTopic();
    
  /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> topicCommand);
    const std::vector<std::string> getTopicParams(void) const;
    const std::string getTopicMessage(void) const;

    /*================= COMMAND CHECKING ================*/
    //int checkTopicParams(std::vector<std::string> messageVec);
    //bool isAllowedChar(char usernameChar);
  
    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _topicParamsVec;
    std::string _topicMessage;
};

#endif
