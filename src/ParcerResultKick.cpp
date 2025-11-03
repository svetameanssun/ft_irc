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




/*==========================================================*/

/*----------------------------------------------------------*/
/*                   IS_VALID_CHANNEL_NAME                  */
/*----------------------------------------------------------*/
bool ParcerResultKick::isValidChanNameChar(int c) {
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

bool ParcerResultKick::isValidChanName(std::string channelName) {
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

bool ParcerResultKick::isSpecialChar(int c) {
    std::string specialChars = "[]\\`^{}";
    if(specialChars.find(c) == std::string::npos) {
        std::cout << "char: " << c << "\n";
        return (0);
    }
    return (1);
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
	for(int i; i <messageVector.size(); i++){
		if (messageVector[i].find(':') != std::string::npos)
			break;
	}
	if (i + 1 == messageVec.size()){
		this->_kickComment = "default";
	}
	else{
		int save_i = i;
		this->_kickComment.push_back('\0');
		for (;i < messageVector.size(); i++){
			this->_kickComment+=messageVector[i];
		}
		messageVector.resize(save_i + 1);
	}
	//I am not quite sure about this condition.
	if (_kickComment.find('\r') != std::string::npos || _kickComment.find('\n') != std::string::npos){
		return (ERR_UNKNOWNCOMMAND);
	}
	//if everything is OK returns 0;
	return (0);
}

int  ParcerResultKick::fillKickParams(std::vector<std::string> messageVector){
	std:vector <std::string> channels;
	std:vector <std::string> users;
	if (messageVector[1].find(',') != std::string::npos){
		channels = stringToVec(messageVector[1], ',');
	}
	else{
		channels[0] = messageVector[1];
	}
	if (messageVector[2].find(',') != std::string::npos){
		users = stringToVec(messageVector[2], ',');
	}
	else{
		users[0] = messageVector[2];
	}
	if (channels.size() != 1 && channels.size() != users.size()){
		return (ERR_NEEDLESSPARAMS);
	}
	for (size_t i = 0; i < users.size(); i++){
		(!isValidNick(users[i])){
			return (ERR_UNKNOWNCOMMAND);
		}
		if (i < channels.size()){
			if(!isValidChanName(channels[i])){
				return (ERR_UNKNOWNCOMMAND);
			}
		}
	}
	this->_kickParamsMap = vectorsToMap(channels, users);
	//if everything is OK returns 0;
	return (0):
}

int ParcerResultKick::checkKickParams(std::vector <std::string> messageVector){
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	int res;
	if (res = checkKickComment(messageVector) > 0); // if :trailing param exists, we will set it as _kickComment, if not, it will be default
	// setKickComment also checks if the trailing comment is valid
	{
		return res;
	}
	//after that the _kickParamsVec should already be set, without trailing params
	res = checkChanAndNick(messageVector);
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
	for (size_t i = 0; )
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
