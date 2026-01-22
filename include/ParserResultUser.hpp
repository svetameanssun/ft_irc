#ifndef PARSERRESULTUSER_HPP
#define PARSERRESULTUSER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultUser : public AParserResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParserResultUser();
    ParserResultUser(const ParserResultUser &other);
    ParserResultUser& operator=(const ParserResultUser& other);
    ~ParserResultUser();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> userCommand);
    void setRealname(std::string name);
    void setRealname(std::string name);
    const std::vector<std::string> getUserParams(void) const;
    const std::string getRealname(void) const;
    const std::string getUsername(void) const;
    

    /*================= COMMAND CHECKING ================*/
    bool isAllowedChar(char realnameChar);
    int checkUserParams(std::vector<std::string> messageVec);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _userParamsVec;
    std::string _realname;
    std::string _username;
};

#endif
