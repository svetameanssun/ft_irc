#include "ParcerResultKick.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultKick::ParcerResultKick()
    : AParcerResult() {
    _command = "KICK";
}

ParcerResultKick::ParcerResultKick(const ParcerResultKick& other): AParcerResult() {
    this->_command = other._command;
    this->_kickParamsVec = other._kickParamsVec;
}


ParcerResultKick& ParcerResultKick::operator=(const ParcerResultKick& other) {
    if(this != &other) {
        this->_kickParamsVec = other._kickParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultKick::~ParcerResultKick() {}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultKick::setParams(std::vector<std::string> kickCommand) {
    if(!kickCommand.empty()) {
        kickCommand.erase(kickCommand.begin());  // drop the first element, wich is the kick command
    }
    this->_kickParamsVec = kickCommand;
}

const std::vector<std::string> ParcerResultKick::getKickParams(void) const{
	return (_kickParamsVec);
}

const std::vector<std::string> getKickChannelsVec(void) const{
	return(this->_kickChannelsVec);
}

const std::vector<std::string> getKickUsersVec(void) const{
	return(this->_kickUsersVec);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                     IS_VALID_NICKNAME                    */
/*----------------------------------------------------------*/

bool ParcerResultKick::isSpecialChar(int c) {
    std::string specialChars = "[]\\`^{}";
    if(specialChars.find(c) == std::string::npos) {
        return (false);
    }
    return (true);
}

bool ParcerResultKick::isValidNick(std::string nickname) {
    std::cout << nickname << "\n";
    if(nickname.empty()) {
        return (0);
    }
    if(nickname.at(0) == '-' || isdigit(nickname.at(0))) {
        return (0);
    }
    if(!isalpha(nickname.at(0)) && !isSpecialChar(nickname.at(0))) {
        return (0);
    }
    if(nickname.length() > 9) {
        return (0);
    }
    for(long unsigned int i = 1; i < nickname.length(); ++i) {
        if(!isdigit(nickname.at(i)) && !isalpha(nickname.at(i)) &&
                !isSpecialChar(nickname.at(i)) && nickname.at(i) != '-') {
            return (0);
        }
    }
    return (1);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                     IS_VALID_COMMAND                    */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
int  ParcerResultKick::checkKickComment (std::vector<std::string> &messageVector){
	for(int i = 0; i < messageVector.size(); i++){
		if (messageVector[i].find(':') != std::string::npos)
			break;
	}
	if (i == messageVector.size() && i == 3){
		this->_kickComment = "default";
	}
	else if (i == messageVector.size() && i > 3){
		this->_kickComment = messageVector[3];
	}
	else{
		int save_i = i;
		for (; i < messageVector.size(); i++){
			this->_kickComment += messageVector[i];
		}
		//here we cut off the comment that we already saved in _kickComment
		messageVector.resize(save_i + 1);
	}
	//I am not quite sure about this condition.
	if (_kickComment.find('\r') != std::string::npos || _kickComment.find('\n') != std::string::npos){
		return (ERR_UNKNOWNCOMMAND);
	}
	
	//here we erase the ':' from the begining of the message
	//we send to the kicked out user.
	if(_kickComment.at(0) == ':'){
				_kickComment.erase(0, 1);
	}
	//if everything is OK returns 0;
	return (0);
}

int  ParcerResultKick::fillKickParams(std::vector<std::string> messageVector){
	//std::vector <std::string> channels;
	//std::vector <std::string> users;
	if (messageVector[1].find(',') != std::string::npos){
		_kickChannelsVec = stringToVec(messageVector[1], ',');
	}
	else{
		_kickChannelsVec.push_back(messageVector[1]);
	}
	if (messageVector[2].find(',') != std::string::npos){
		_kickUsersVec = stringToVec(messageVector[2], ',');
	}
	else{
		_kickUsersVec.push_back(messageVector[2]);
	}
	if (_kickChannelsVec.size() != 1 && _kickChannelsVec.size() != _kickUsersVec.size()){
		return (ERR_NEEDLESSPARAMS);
	}
	for (size_t i = 0; i < _kickUsersVec.size(); i++){
		if (!isValidNick(_kickUsersVec[i])){
			return (ERR_UNKNOWNCOMMAND);
		}
		if (i < _kickChannelsVec.size()){
			if (!isValidChanName(_kickChannelsVec[i])){
				return (ERR_UNKNOWNCOMMAND);
			}
		}
	}
	this->_kickParamsMap = vectorsToMap(_kickChannelsVec, _kickUsersVec);
	//if everything is OK returns 0;
	return (0);
}

int ParcerResultKick::checkKickParams(std::vector <std::string> messageVector){
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	}
	int res = checkKickComment(messageVector);
	if (res > 0); // if :trailing param exists, we will set it as _kickComment, if not, it will be default
	// setKickComment also checks if the trailing comment is valid{
		return res;
	}
	//after that the _kickParamsVec should already be set, without trailing params
	res = fillKickParams(messageVector);
	return (res);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                   SPLIT_AND_UNITE                        */
/*----------------------------------------------------------*/
const std::vector<std::string> ParcerResultKick::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

std::map<int, std::vector<std::string>> ParcerResultKick::vectorsToMap(std::vector<std::string> channels, std::vector<std::string>users){
	std::map <int, std::vector<std::string>> map;
	if (channels.size() == 1 && users.size() == 1){
		map[0].push_back(channels[0]);
        map[0].push_back(users[0]);
	}
	else if (channels.size() == 1){
		for (size_t i = 0; i < users.size(); ++i){
			map[i].push_back(channels[0]);
			map[i].push_back(users[i]);
		}
	}
	else{
		for (size_t i = 0; i < users.size(); ++i){
			map[i].push_back(channels[i]);
			map[i].push_back(users[i]);
		}
	}
	return map;
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultKick::printResult()const {

    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_kickParamsVec.begin();
            itVec != this->_kickParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/

/*For the message to be syntactically correct, there MUST be
   either one channel parameter and multiple user parameter, 
   Ex: KICK channel person1 person2 person3 ...
 
   or as many channel parameters as there are user parameters.
   Ex: KICK channel person
   
   If a "comment" is given, this will be sent instead of the default message,
   the Kickname of the user issuing the KICK.

   Ex: KICK #Finnish John :Speaking English
 */
