#ifndef PARSERRESULTKICK_HPP
#define PARSERRESULTKICK_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultKick : public AParserResult {
public:
    /*================= CANONICAL FORM =================*/
    ParserResultKick();
    ParserResultKick(const ParserResultKick &other);
    ParserResultKick &operator=(const ParserResultKick &other);
    virtual ~ParserResultKick();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> kickCommand);
    const std::vector<std::string> getKickParams(void) const;
    const std::vector<std::string> getKickChannelsVec(void) const;
    const std::vector<std::string> getKickUsersVec(void) const;
    const std::string getKickComment(void) const;
    const std::map<int, std::vector<std::string> > getKickParamsMap(void) const;
    
    
    /*================= VALIDATION ======================*/
    //bool isValidChanNameChar(int c);
    //bool isValidChanName(std::string channelName);

    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

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
    std::map<int, std::vector<std::string> > _kickParamsMap;  // Maps index → [index] = {channel, user}
    std::vector <std::string> _kickChannelsVec;// channels in order (where the user's being kicked out)
    std::vector <std::string> _kickUsersVec; // users being kicked out
    std::string _kickComment;                  // Optional trailing comment
};

#endif
