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
/*                   IS_VALID / IS_SPECIAL                  */
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

int ParcerResultJoin::checkKickCommand(std::vector <std::string> messageVector){
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	
	
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
