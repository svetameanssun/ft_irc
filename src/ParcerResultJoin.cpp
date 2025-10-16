#include "ParcerResultJoin.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultJoin::ParcerResultJoin()
    : AParcerResult() {
    _command = "JOIN";
}

ParcerResultJoin::ParcerResultJoin(const ParcerResultJoin &other): AParcerResult() {
    this->_command = other._command;
    this->_joinParamsVec = other._joinParamsVec;
    this->_joinParamsMap = other._joinParamsMap;
}

ParcerResultJoin& ParcerResultJoin::operator=(const ParcerResultJoin& other) {
    if(this != &other) {
        this->_joinParamsVec = other._joinParamsVec;
        this->_joinParamsMap = other._joinParamsMap;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultJoin::~ParcerResultJoin() {
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultJoin::setParams(std::vector<std::string> joinCommand) {
    if(joinCommand.size() == 2) {
        if (!joinCommand.empty()) {
            joinCommand.erase(joinCommand.begin());  // drop the first element, which is the command itself
        }
        this->_joinParamsVec = joinCommand;
    } else if(joinCommand.size() == 3) {
        if (!joinCommand.empty()) {
            joinCommand.erase(joinCommand.begin());  // drop the first element, which is the command itself
        }
        this->_joinParamsVec = joinCommand;
        this->_joinParamsMap = stringsToMap(joinCommand.at(1), joinCommand.at(2));
    } else {
        (void)joinCommand;
    }
}

const std::map<std::string, std::string> ParcerResultJoin::getJoinParamsMap(void) const {
    return (_joinParamsMap);
}

const std::vector <std::string> ParcerResultJoin::getJoinParamsVec(void) const {
    return (_joinParamsVec);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                       IS_VALID...                        */
/*----------------------------------------------------------*/

bool ParcerResultJoin::isValidChanNameChar(int c) {
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
bool ParcerResultJoin::isValidChanName(std::string channelName) {
    size_t i = 0;
    if(channelName.empty()) {
        // NOT FORGET EVERYWHERE!
        return false;
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

bool ParcerResultJoin::isValidJoin(std::vector <std::string> messageVector) {

    std::map<std::string, std::string> joinParamsMap;
    std::vector <std::string> joinParamsVec;

    if(messageVector.size() == 2) {
        joinParamsVec = stringToVec(messageVector[1], ',');
        for(size_t i = 0; i < joinParamsVec.size(); i++) {
            if(!isValidChanName(joinParamsVec.at(i))) {
                return (false);
            }
        }
    } else if(messageVector.size() == 3) {
        std::vector<std::string> joinChannels = stringToVec(messageVector[1], ',');
        std::vector<std::string> joinPasswords = stringToVec(messageVector[2], ',');
        if(joinChannels.size() < joinPasswords.size()) {
            return (false);
        }
        joinParamsMap = stringsToMap(messageVector[1], messageVector[2]);
        for(std::map<std::string, std::string>::iterator it = joinParamsMap.begin(); it != joinParamsMap.end(); ++it) {
            if(!isValidChanName(it->first))
                return (false);
        }
    } else
        return (false);
    return (true);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                   SPLIT AND UNITE                        */
/*----------------------------------------------------------*/
const std::vector<std::string> ParcerResultJoin::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}


const std::map<std::string, std::string> ParcerResultJoin::stringsToMap(std::string keyString, std::string valueString) {
    std::vector<std::string> keyVec = stringToVec(keyString, ','); // vector of keys, channel names
    std::vector<std::string> valueVec = stringToVec(valueString, ','); // vector of channel passwords
    std::map<std::string, std::string> resMap;

    std::vector<std::string>::iterator itKey = keyVec.begin();
    std::vector<std::string>::iterator itVal = valueVec.begin();

    for(; itKey != keyVec.end(); ++itKey) {
        std::string value;
        if(itVal != valueVec.end() && !itVal->empty())
            value = *itVal;
        else
            value = "";
        resMap[*itKey] = value;
        if(itVal != valueVec.end())
            ++itVal;
    }
    return resMap;
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/
void ParcerResultJoin::printResult() const {
    if(!this->_joinParamsMap.empty()) {
        std::cout << "[KEY] = VALUE\n";
        for(std::map<std::string, std::string>::const_iterator itMap = this->_joinParamsMap.begin();
                itMap  != this->_joinParamsMap.end(); ++itMap) {
            std::cout << "[" << itMap ->first << "] = " << itMap->second << "\n";
        }
    }
    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_joinParamsVec.begin();
            itVec != this->_joinParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/
