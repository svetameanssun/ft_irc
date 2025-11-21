#ifndef PARCERRESULTPRIVMSG_HPP
#define PARCERRESULTPRIVMSG_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultPrivmsg : public AParcerResult {
  public:
    /*================= CANONICAL FORM =================*/
    ParcerResultPrivmsg();
    ParcerResultPrivmsg(const ParcerResultPrivmsg &other);
    ParcerResultPrivmsg& operator=(const ParcerResultPrivmsg& other);
    ~ParcerResultPrivmsg();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> privmsgCommand);
    const std::vector<std::string> getPrivmsgParams(void) const;

    /*================= VALIDATION ======================*/
    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkPrivmsgTarget(std::string privmsgTarget);
    int checkPrivmsgParams(std::vector <std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult() const;
  private:
    std::vector <std::string> _privmsgParamsVec;
    std::vector <std::string> _targetVec;
    std::string _privmsgMessage;
};

#endif
