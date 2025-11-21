#ifndef PARCERRESULTNOTICE_HPP
#define PARCERRESULTNOTICE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultNotice : public AParcerResult {
  public:
    ParcerResultNotice();
    ParcerResultNotice(const ParcerResultNotice &other);
    ParcerResultNotice& operator=(const ParcerResultNotice& other);
    ~ParcerResultNotice();
    
    void setParams(std::vector<std::string> noticeCommand);
    const std::vector<std::string> getNoticeParams(void) const;
    void printResult() const;
    const std::vector<std::string> stringToVec(std::string str, char delim);
    int checkNoticeTarget(std::string noticeTarget);
    int checkNoticeParams(std::vector <std::string> messageVector);
  private:
    std::vector <std::string> _targetVec;
    std::vector <std::string> _noticeParamsVec;
    std::string _noticeMessage;
};

#endif
