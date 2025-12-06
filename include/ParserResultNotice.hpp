#ifndef PARSERRESULTNOTICE_HPP
#define PARSERRESULTNOTICE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultNotice : public AParserResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParserResultNotice();
    ParserResultNotice(const ParserResultNotice &other);
    ParserResultNotice& operator=(const ParserResultNotice& other);
    ~ParserResultNotice();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> noticeCommand);
    const std::vector<std::string> getNoticeParams(void) const;
    const std::vector<std::string> getTargetVec(void) const;
    const std::string getNoticeMessage(void) const;

    /*================= COMMAND CHECKING ================*/
    int checkNoticeTarget(std::string noticeTarget);
    int checkNoticeParams(std::vector <std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _targetVec;
    std::vector <std::string> _noticeParamsVec;
    std::string _noticeMessage;
};

#endif
