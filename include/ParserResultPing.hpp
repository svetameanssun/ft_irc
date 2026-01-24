#ifndef PARSERRESULTPING_HPP
#define PARSERRESULTPING_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultPing : public AParserResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParserResultPing();
    ParserResultPing(const ParserResultPing &other);
    ParserResultPing& operator=(const ParserResultPing& other);
    ~ParserResultPing();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> pingCommand);
    const std::vector<std::string> getPingParams(void) const;
    const std::string getPingMessage(void) const;

    /*================= VALIDATION ======================*/
    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkPingParams(std::vector <std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _pingParamsVec;
    std::string _pingMessage;
};

#endif
