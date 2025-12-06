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
    /*================= CANONICAL FORM =================*/
    ParcerResultPass();
    ParcerResultPass(const ParcerResultPass &other);
    ParcerResultPass& operator=(const ParcerResultPass& other);
    ~ParcerResultPass();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> passCommand);
    const std::vector<std::string> getPassParams(void) const;

     /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;

  private:
    std::vector <std::string> _passParamsVec; // to make it unified,
                                          // I pass the password as a vec, but it is actually a string
};

#endif
