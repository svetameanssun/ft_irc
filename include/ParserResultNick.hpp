#ifndef PARSERRESULTNICK_HPP
#define PARSERRESULTNICK_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultNick : public AParserResult {
  public:
    ParserResultNick();
    ParserResultNick(const ParserResultNick &other);
    ParserResultNick& operator=(const ParserResultNick& other);
    ~ParserResultNick();
    void setParams(std::vector<std::string> nickCommand);
    const std::string getNickname(void) const;
    void printResult() const;

    //bool isSpecialChar(int c);
    //bool isValidNick(std::vector<std::string> nickCommand);
    
  private:
    //std::vector <std::string> _nickParamsVec; // we acatually do not need this attribute
    std::string _nickname;
};

#endif