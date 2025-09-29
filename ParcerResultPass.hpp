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
    
    void setPassParams(std::vector<std::string> passCommand);//
    const std::vector<std::string> getPassParams(void) const;
  private:
    std::vector <std::string> _passParams; // to make it unified,
                                          // I pass the password as a vec, but it is actually a string
};

#endif