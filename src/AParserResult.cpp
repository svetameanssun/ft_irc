#include "AParserResult.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

AParserResult::AParserResult(){}

AParserResult::AParserResult(std::string command){
    this->_command = command;
}

AParserResult::AParserResult(const AParserResult &other){
    this->_command = other._command;
}

AParserResult& AParserResult::operator=(const AParserResult& other){
    if (this != &other)
    {
        this->_command = other._command;
    }
    return (*this);
}

std::string AParserResult::getCommand()const{
    return (_command);
}

AParserResult::~ AParserResult() {} // "required if not using Microsoft extension" taken from https://learn.microsoft.com/en-us/cpp/cpp/abstract-classes-cpp?view=msvc-170
/*==========================================================*/
/*----------------------------------------------------------*/
/*                   IS_VALID_CHANNEL_NAME                  */
/*----------------------------------------------------------*/
bool AParserResult::isValidChanNameChar(int c) {
    if(c == '\0')
        return (false);
    else if(c == '\a')
        return (false);
    else if(c == '\r')
        return (false);
    else if(c == '\n')
        return (false);
    else if(c == ' ')
        return (false);
    else if(c == ',')
        return (false);
    else if(c == ':')
        return (false);
    else {
        return (true);
    }
}

//checks the channel name requirements
// and checks whether this excact channelName complies with these requirements
// returns false if the name is not valid.
bool AParserResult::isValidChanName(std::string channelName) {
    size_t i = 0;
    if(channelName.empty()) {
        // NOT FORGET EVERYWHERE!
        return (false);
    }
    if((channelName.at(0) != '#') && (channelName.at(0) != '&')) {
        std::cout << "THIS\n";
        return (false);
    }
    if((channelName.length() > 200) || (channelName.length() == 1)) {
        return (false);
    }
    i++;
    for(; i < channelName.length(); ++i) {
        if(!isValidChanNameChar(channelName.at(i))) {
            return (false);
        }
    }
    return (true);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                     IS_VALID_NICKNAME                    */
/*----------------------------------------------------------*/

bool AParserResult::isSpecialChar(int c) {
    std::string specialChars = "[]\\`^{}";
    if(specialChars.find(c) == std::string::npos) {
        return (false);
    }
    return (true);
}

bool AParserResult::isValidNick(std::string nickname) {
    std::cout << nickname << "\n";
    if(nickname.empty()) {
        return (false);
    }
    if(nickname.at(0) == '-' || isdigit(nickname.at(0))) {
        return (false);
    }
    if(!isalpha(nickname.at(0)) && !isSpecialChar(nickname.at(0))) {
        return (false);
    }
    if(nickname.length() > 9) {
        return (false);
    }
    for(long unsigned int i = 1; i < nickname.length(); ++i) {
        if(!isdigit(nickname.at(i)) && !isalpha(nickname.at(i)) &&
                !isSpecialChar(nickname.at(i)) && nickname.at(i) != '-') {
            return (false);
        }
    }
    return (true);
}

/*==========================================================*/