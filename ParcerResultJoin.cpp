#include "ParcerResultJoin.hpp"

ParcerResultJoin::ParcerResultJoin() {
}

ParcerResultJoin::ParcerResultJoin(const ParcerResultJoin &other){
    this->_joinResVec = other._joinResVec;
    this->_joinResMap = other._joinResMap;
}

ParcerResultJoin& ParcerResultJoin::operator=(const ParcerResultJoin& other){
    if (this != &other)
    {
        this->_joinResVec = other._joinResVec;
        this->_joinResMap = other._joinResMap;
    }
    return (*this);

}

ParcerResultJoin::~ParcerResultJoin() {
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
    std::vector<std::string> keyVec = stringToVec(keyString, ',');
    std::vector<std::string> valueVec = stringToVec(valueString, ',');
    std::map <std::string, std::string> resMap;
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    it2 = valueVec.begin();
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


bool isValidChannelName(std::string channelName){
    //check the channel name requirements
    // and check whether this excact channelName complies with these requirements
    // return false if the name is not valid.

}

bool ParcerResultJoin::isValidJoin(std::vector <std::string> messageVector){
   
    if (messageVector.size() == 2){
        _joinResVec = stringToVec(messageVector[1], ',');
        for(int i = 0; this->_joinResVec.size(); i++){
            if (!isValidChannelName(_joinResVec.at(i)))
                return (ERR_UNKNOWNCOMMAND);
        }
        //check, how many channels i want to join
        //  make a vector out of channels
         //!= '#' && first != '&' && first != '+' && first != '!'
         //&foo,+bar,#foof
    }

    if (messageVector.size() == 3){
        _joinResMap = stringsToMap(messageVector[1], messageVector[2]);
        for (std::map<std::string, std::string>::iterator it = _joinResMap.begin(); it != _joinResMap.end(); ++it){
            if (!isValidChannelName(it->first) || !isValidChannelName(it->second))
                return (ERR_UNKNOWNCOMMAND);
        }
        //check how many channels I want to join//
        // make a map [key] - channels name/
        //            value - password.
        //&foo,+bar,#foof
        //fubar,foobar
    }
    
}




void ParcerResultJoin::setChannelNamePassMap(std::map<std::string, std::string> joinResMap) {
    this->_joinResMap= joinResMap;
}

void ParcerResultJoin::setChannelNameVec(std::vector <std::string> joinResVec) {
    this->_joinResVec = joinResVec;
}

const std::map<std::string, std::string> ParcerResultJoin::getChannelNamePassMap(void) const {
    return (_joinResMap);
}

const std::vector <std::string> ParcerResultJoin::getChannelNameVec(void) const {
    return (_joinResVec);
}

