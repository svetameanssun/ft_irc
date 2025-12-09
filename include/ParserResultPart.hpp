#ifndef PARSERRESULTPART_HPP
#define PARSERRESULTPART_HPP

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "AParserResult.hpp"


class ParserResultPart : public AParserResult {
public:
    /*================= CANONICAL FORM =================*/
    ParserResultPart();
    ParserResultPart(const ParserResultPart &other);
    ParserResultPart &operator=(const ParserResultPart &other);
    virtual ~ParserResultPart();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> partCommand);
    const std::vector<std::string> getPartParams(void) const;
    const std::vector<std::string> getPartChannelsVec(void) const;
    const std::string getPartMessage(void) const;
    
    /*================= VALIDATION ======================*/
    //bool isValidChanNameChar(int c);
    //bool isValidChanName(std::string channelName);

    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkPartMessage(std::vector<std::string> &messageVector);
    int fillPartParams(std::vector<std::string> messageVector);
    int checkPartParams(std::vector<std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult(void) const;
private:
    std::vector<std::string> _partParamsVec;   // Stores raw parameters (after "PART")
    std::vector <std::string> _partChannelsVec;// channels in order (the channels the user is leaving)
    std::string _partMessage;                  // Optional trailing part message
};

#endif