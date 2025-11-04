#ifndef PARCERRESULTKICK_HPP
#define PARCERRESULTKICK_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParcerResult.hpp"


class ParcerResultKick : public AParcerResult {
public:
    /*================= CANONICAL FORM =================*/
    ParcerResultKick();
    ParcerResultKick(const ParcerResultKick &other);
    ParcerResultKick &operator=(const ParcerResultKick &other);
    virtual ~ParcerResultKick();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> kickCommand);
    const std::vector<std::string> getKickParams(void) const;

    /*================= VALIDATION ======================*/
    //bool isValidChanNameChar(int c);
    //bool isValidChanName(std::string channelName);

    bool isSpecialChar(int c);
    bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkKickComment(std::vector<std::string> &messageVector);
    int fillKickParams(std::vector<std::string> messageVector);
    int checkKickParams(std::vector<std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);
    std::map<int, std::vector<std::string> > vectorsToMap(
        std::vector<std::string> channels,
        std::vector<std::string> users
    );

    /*================= DEBUG / OUTPUT ==================*/
    void printResult(void) const;
private:
    std::vector<std::string> _kickParamsVec;   // Stores raw parameters (after "KICK")
    std::map<int, std::vector<std::string> > _kickParamsMap;  // Maps index → [channel, user]
    std::string _kickComment;                  // Optional trailing comment
};

#endif // PARCERRESULTKICK_HPP
