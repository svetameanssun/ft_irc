#ifndef PARCERRESULTNICK_HPP
#define PARCERRESULTNICK_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultNick : public AParcerResult {
  public:
    ParcerResultNick();
    ParcerResultNick(const ParcerResultNick &other);
    ParcerResultNick& operator=(const ParcerResultNick& other);
    ~ParcerResultNick();
    void setParams(std::vector<std::string> nickCommand);
    const std::vector<std::string> getNickParams(void) const;
    void printResult() const;

    bool isSpecialChar(int c);
    bool isValidNick(std::vector<std::string> nickCommand);
    
  private:
    std::vector <std::string> _nickParamsVec;
};

#endif