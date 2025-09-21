#ifndef PARCERRESULTNICK_HPP
#define PARCERRESULTNICK_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultPass : public AParcerResult {
  public:
    ParcerResultPass();
    ~ParcerResultPass();
  private:
    std::vector <std::string> _passParams;
};

#endif