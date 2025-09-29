#include "ParcerResultJoin.hpp"

ParcerResultJoin::ParcerResultJoin()
    : AParcerResult("JOIN") {
}

ParcerResultJoin::ParcerResultJoin(const ParcerResultJoin &other)
    : AParcerResult("JOIN"){
    this->_joinParamsVec = other._joinParamsVec;
    this->_joinParamsMap = other._joinParamsMap;
}

ParcerResultJoin& ParcerResultJoin::operator=(const ParcerResultJoin& other){
    if (this != &other)
    {
        this->_joinParamsVec = other._joinParamsVec;
        this->_joinParamsMap = other._joinParamsMap;
    }
    return (*this);
}

void ParcerResultJoin::setJoinParams(std::vector<std::string> joinCommand){
    if (joinCommand.size() == 2){
        if (!joinCommand.empty()) {
            joinCommand.erase(joinCommand.begin());  // drop the first element, which is the command itself
        }
        this->_joinParamsVec = joinCommand;
    }
    else if (joinCommand.size() == 3){
        this->_joinParamsMap = stringsToMap(joinCommand.at(1), joinCommand.at(2));
    }
    else{
        (void)joinCommand;
    }
}

bool ParcerResultJoin::isValidChannelNameChar(int c){
    if (c == '\0')
        return (false);
    else if (c == '\a')
        return (false);
    else if (c == '\r')
        return (false);
    else if (c == '\n')
        return (false);
    else if (c == ' ')
        return (false);
    else if (c == ',')
        return (false);
    else if (c == ':')
        return (false);
    else{
        return (true);
    }
}

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
    std::map <std::string, std::string> resMap;
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    it2 = valueVec.begin(); // passwrods
    for(it1 = keyVec.begin(); it1 != keyVec.end(); it1++) {

        if (it2->empty()){
            resMap[*it1] = "";
        } else {
            resMap[*it1] = *it2;
        }
        it2++;
    }
    return(resMap);
}

 //checks the channel name requirements
// and checks whether this excact channelName complies with these requirements
// returns false if the name is not valid.
bool ParcerResultJoin::isValidChannelName(std::string channelName){
    size_t i = 0;
    if (channelName.empty()){
     // NOT FORGET EVERYWHERE!
        return false;
    }
    if ((channelName.at(0) != '#') && (channelName.at(0) != '&')){
        return (false);
    }
    if ((channelName.length() > 200) || (channelName.length() == 1)){
        return (false);
    }
    i++;
    for (; i < channelName.length(); i++){
        if (!isValidChannelNameChar(channelName.at(i))){
            return (false);
        }
    }
    return (true);
}

bool ParcerResultJoin::isValidJoin(std::vector <std::string> messageVector){
   
    std::map<std::string, std::string> joinParamsMap;
    std::vector <std::string> joinParamsVec;
    if (messageVector.size() == 2){
        joinParamsVec = stringToVec(messageVector[1], ',');
        for(int i = 0; joinParamsVec.size(); i++){
            if (!isValidChannelName(joinParamsVec.at(i)))
                return (false);
        }
    }
    else if (messageVector.size() == 3){
        joinParamsMap = stringsToMap(messageVector[1], messageVector[2]);
        for (std::map<std::string, std::string>::iterator it = joinParamsMap.begin(); it != joinParamsMap.end(); ++it){
            if (!isValidChannelName(it->first) || !isValidChannelName(it->second))
                return (false);
        }
    }
    else
        return (false);
    return (true);
}


const std::map<std::string, std::string> ParcerResultJoin::getJoinParamsMap(void) const {
    return (_joinParamsMap);
}

const std::vector <std::string> ParcerResultJoin::getJoinParamsVec(void) const {
    return (_joinParamsVec);
}

ParcerResultJoin::~ParcerResultJoin() {
}

