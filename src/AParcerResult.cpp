#include "AParcerResult.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

AParcerResult::AParcerResult(){}

AParcerResult::AParcerResult(std::string command){
    this->_command = command;
}

AParcerResult::AParcerResult(const AParcerResult &other){
    this->_command = other._command;
}

AParcerResult& AParcerResult::operator=(const AParcerResult& other){
    if (this != &other)
    {
        this->_command = other._command;
    }
    return (*this);
}

std::string AParcerResult::getCommand()const{
    return (_command);
}

AParcerResult::~ AParcerResult() {} // "required if not using Microsoft extension" taken from https://learn.microsoft.com/en-us/cpp/cpp/abstract-classes-cpp?view=msvc-170
/*==========================================================*/
/*----------------------------------------------------------*/
/*                   IS_VALID_CHANNEL_NAME                  */
/*----------------------------------------------------------*/
bool AParcerResult::isValidChanNameChar(int c) {
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
bool AParcerResult::isValidChanName(std::string channelName) {
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
