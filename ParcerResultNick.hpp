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
    ~ParcerResultNick();

    bool isSpecialChar(int c);
    bool isValidNick(std::string nick)
    
  private:
    std::vector <std::string> _nickParams;
};

#endif