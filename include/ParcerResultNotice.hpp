#ifndef PARCERRESULTNOTICE_HPP
#define PARCERRESULTNOTICE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultNotice : public AParcerResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParcerResultNotice();
    ParcerResultNotice(const ParcerResultNotice &other);
    ParcerResultNotice& operator=(const ParcerResultNotice& other);
    ~ParcerResultNotice();

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
