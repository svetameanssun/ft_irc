#include "ParcerResultJoin.hpp"

ParcerResultJoin::ParcerResultJoin() {
}

bool CommandDispatcher::isValidJoin(std::vector <std::string> messageVector){
   
    parcRes = 
    if (messageVector.size() == 2){
        parcRes->setChannelnameVec(parcRes->stringToVec(messageVector[1]));
        //check, how many channels i want to join
        //  make a vector out of channels
        // and then handle("JOIN", channelVec)
         //!= '#' && first != '&' && first != '+' && first != '!'
         //&foo,+bar,#foof
    }

    if (messageVector.size() == 3){
        parcRes.setChannelNamePassMap(parcRes.stringsToMap(messageVector[1], messageVector[2]));
        //check how many channels I want to join//
        // make a map [key] - channels name/
        //            value - password.
        // and then handle("JOIN", channelMap)
        //&foo,+bar,#foof
        //fubar,foobar
    }
}




void ParcerResultJoin::setChannelNamePassMap(std::map<std::string, std::string> ParcerResult::joinResMap()) {
    this->_channelNamePassMap = joinResMap;
}

void ParcerResultJoin::setChannelnameVec(std::vector <std::string> ParcerResult::joinResVec()) {
    this->_channelNameVec = joinResVec;
}

cosnt std::map<std::string, std::string> ParcerResultJoin::getChannelNamePassMap(void) const {
    return (_channelNamePassMap);
}

const std::vector <std::string> ParcerResultJoin::getChannelNameVec(void) const {
    return (_channelNameVec);
}

ParcerResultJoin::~ParcerResultJoin() {
}
