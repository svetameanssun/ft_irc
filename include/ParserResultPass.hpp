#ifndef PARSERRESULTPASS_HPP
#define PARSERRESULTPASS_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultPass : public AParserResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParserResultPass();
    ParserResultPass(const ParserResultPass &other);
    ParserResultPass& operator=(const ParserResultPass& other);
    ~ParserResultPass();

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
