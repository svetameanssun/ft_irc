#ifndef PARSERRESULTQUIT_HPP
#define PARSERRESULTQUIT_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultQuit : public AParserResult {
public:
    /*================= CANONICAL FORM =================*/
    ParserResultQuit();
    ParserResultQuit(const ParserResultQuit &other);
    ParserResultQuit &operator=(const ParserResultQuit &other);
    virtual ~ParserResultQuit();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> quitCommand);
    const std::vector<std::string> getQuitParams(void) const;
    const std::string getQuitMessage(void) const;
    
    /*================= COMMAND CHECKING ================*/
    void collectQuitMessage(std::vector<std::string> &messageVector);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult(void) const;
private:
    std::vector<std::string> _quitParamsVec;   // Stores raw parameters (including quitMessage)
    std::string _quitMessage;                  // Optional trailing quit message
};

#endif
