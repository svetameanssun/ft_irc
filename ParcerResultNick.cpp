#include "ParcerResultNick.hpp"

bool ParcerResultNick::isSpecialChar(int c){
    
    std::string specialChars = "[]\\`^{}";
    if (specialChars.find(c) ==  std::string::npos)
        return (0);
    return (1);
}

bool ParcerResultNick::isValidNick(std::string nick){
    if (nick.empty())
        return (0);
    if (nick.at(0) == '-' || isdigit(nick.at(0)))
        return (0);
    if (!isalpha(nick.at(0)) && !isSpecialChar(nick.at(0)))
        return (0);
    if (nick.length() > 9)
        return (0);
    for (int i = 1; i < nick.length(); ++i){
        if (nick.at(i) > 127) // non-ASCII
            return 0;
        if (!isdigit(nick.at(i)) && !isalpha(nick.at(i)) && !isSpecialChar(nick.at(i)) && nick.at(i) != '-')
            return (0);
    }
    return (1);
}