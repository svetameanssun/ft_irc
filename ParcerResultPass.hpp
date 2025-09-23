#ifndef PARCERRESULTPASS_HPP
#define PARCERRESULTPASS_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultPass : public AParcerResult {
  public:
    ParcerResultPass();
    ParcerResultPass(const ParcerResultPass &other);
    ParcerResultPass& operator=(const ParcerResultPass& other);
    ~ParcerResultPass();
    
    void setPassParams(std::vector<std::string> nickCommand);
    const std::vector<std::string> getPassParams(void) const;
  private:
    std::vector <std::string> _passParams;
};

#endif