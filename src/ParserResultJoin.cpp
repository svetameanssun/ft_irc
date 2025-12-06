#include "ParserResultJoin.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParserResultJoin::ParserResultJoin()
    : AParserResult() {
    _command = "JOIN";
}

ParserResultJoin::ParserResultJoin(const ParserResultJoin &other): AParserResult() {
    this->_command = other._command;
    this->_joinParamsVec = other._joinParamsVec;
    this->_joinChannelsVec = other._joinChannelsVec;
    this->_joinPasswordsVec = other._joinPasswordsVec;
}

ParserResultJoin& ParserResultJoin::operator=(const ParserResultJoin& other) {
    if(this != &other) {
        this->_command = other._command;
        this->_joinParamsVec = other._joinParamsVec;
        this->_joinChannelsVec = other._joinChannelsVec;
        this->_joinPasswordsVec = other._joinPasswordsVec;
    }
    return (*this);
}

ParserResultJoin::~ParserResultJoin() {
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultJoin::setParams(std::vector<std::string> joinCommand) {
    if (!joinCommand.empty()) {
        joinCommand.erase(joinCommand.begin());  // drop the first element, which is the command itself
    }
    this->_joinParamsVec = joinCommand;
    this->_joinChannelsVec = stringToVec(this->_joinParamsVec[0]);
    if (joinCommand.size() == 2){
        this->_joinPasswordsVec = stringToVec(this->_joinParamsVec[1]);
    }
}

const std::vector <std::string> ParserResultJoin::getJoinParamsVec(void) const {
    return (_joinParamsVec);
}

const std::vector <std::string> ParserResultJoin::getJoinChannelsVec(void) const {
    return (_joinChannelsVec);
}

const std::vector <std::string> ParserResultJoin::getJoinPasswordsVec(void) const {
    return (_joinPasswordsVec);
}

const bool ParserResultJoin::getLeaveAllChansFlag(void) const{
    return (_leaveAllChans);
}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                       IS_VALID_JOIN                      */
/*----------------------------------------------------------*/

int ParserResultJoin::checkJoinParams(std::vector <std::string> messageVector) {

    std::vector <std::string> joinChannelsVec;

    if (messageVec.size() < 2){
        delete(resultJoin);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 3){
        delete(resultJoin);
        return ERR_NEEDLESSPARAMS;
    }
    if (messageVector.size == 2 && messageVector.at(1) == "0"){
        this->leaveAllChans = true;
        return (0);
    }
    this->leaveAllChans = false;
    joinChannelsVec = stringToVec(messageVector[1], ',');
    for(size_t i = 0; i < joinParamsVec.size(); i++) {
        if(!isValidChanName(joinParamsVec.at(i))) {
            return (ERR_NOSUCHCHANNEL);
        }
    }
    return (0);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                   SPLIT AND UNITE                        */
/*----------------------------------------------------------*/
const std::vector<std::string> ParserResultJoin::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}


/*const std::map<std::string, std::string> ParserResultJoin::stringsToMap(std::string keyString, std::string valueString) {
    std::vector<std::string> keyVec = stringToVec(keyString, ','); // vector of keys, channel names
    std::vector<std::string> valueVec = stringToVec(valueString, ','); // vector of channel passwords
    std::map<std::string, std::string> resMap;

    std::vector<std::string>::iterator itKey = keyVec.begin();
    std::vector<std::string>::iterator itVal = valueVec.begin();
    
 
    std::string value;
    for(; itKey != keyVec.end(); ++itKey) {
        if(itVal != valueVec.end() && !itVal->empty())
            value = *itVal;
        else
            value = "";
        resMap[*itKey] = value;
        if(itVal != valueVec.end())
            ++itVal;
    }
    return resMap;
}*/

/*==========================================================*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/
void ParserResultJoin::printResult() const {
    for(size_t i = 0; i < _joinChannelsVec.size(); ++i){
        std::cout << "CHANNEL NAME: " << _joinChannelsVec.at(i);
        if (i < _joinPasswordsVec.size()){
            std::cout << "PASSWORD: " << _joinPasswordsVec.at(i) << std::endl;
        }
        else {
            std::cout << std::endl; 
        }
    }
}
/*==========================================================*/
