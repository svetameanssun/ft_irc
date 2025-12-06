#ifndef PARSERRESULTPRIVMSG_HPP
#define PARSERRESULTPRIVMSG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultPrivmsg : public AParserResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParserResultPrivmsg();
    ParserResultPrivmsg(const ParserResultPrivmsg &other);
    ParserResultPrivmsg& operator=(const ParserResultPrivmsg& other);
    ~ParserResultPrivmsg();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> privmsgCommand);
    const std::vector<std::string> getPrivmsgParams(void) const;
    const std::vector<std::string> getTargetVec(void) const;
    const std::string getPrivmsgMessage(void) const;

    /*================= VALIDATION ======================*/
    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkPrivmsgTarget(std::string privmsgTarget);
    int checkPrivmsgParams(std::vector <std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _privmsgParamsVec;
    std::vector <std::string> _targetVec;
    std::string _privmsgMessage;
};

#endif
