#ifndef PARCERRESULTQUIT_HPP
#define PARCERRESULTQUIT_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultQuit : public AParcerResult {
public:
    /*================= CANONICAL FORM =================*/
    ParcerResultQuit();
    ParcerResultQuit(const ParcerResultQuit &other);
    ParcerResultQuit &operator=(const ParcerResultQuit &other);
    virtual ~ParcerResultQuit();

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
