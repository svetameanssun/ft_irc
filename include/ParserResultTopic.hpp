#ifndef PARSERRESULTTOPIC_HPP
#define PARSERRESULTTOPIC_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultTopic : public AParserResult {
  public:
  /*================= CANONICAL FORM =================*/
    ParserResultTopic();
    ParserResultTopic(const ParserResultTopic &other);
    ParserResultTopic& operator=(const ParserResultTopic& other);
    ~ParserResultTopic();
    
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
