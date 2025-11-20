#include "ParcerResultInvite.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultInvite::ParcerResultInvite()
    : AParcerResult() {
    _command = "INVITE";
}

ParcerResultInvite::ParcerResultInvite(const ParcerResultInvite& other): AParcerResult() {
    this->_command = other._command;
    this->_inviteParamsVec = other._inviteParamsVec;
}


ParcerResultInvite& ParcerResultInvite::operator=(const ParcerResultInvite& other) {
    if(this != &other) {
        this->_inviteParamsVec = other._inviteParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultInvite::~ParcerResultInvite() {}
/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultInvite::setParams(std::vector<std::string> inviteCommand) {
    if(!inviteCommand.empty()) {
        inviteCommand.erase(inviteCommand.begin());  // drop the first element, wich is the Invite command
    }
    this->_inviteParamsVec = inviteCommand;
}
const std::vector<std::string> ParcerResultInvite::getInviteParams(void) const{
	return (_inviteParamsVec);
}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                   IS_VALID / IS_SPECIAL                  */
/*----------------------------------------------------------*/
int ParcerResultInvite::checkInviteParams(std::vector<std::string> messageVec){
	if (messageVec.size() < 3){
		return (ERR_NEEDMOREPARAMS);
	}
	if (message.size() > 3){
		return (ERR_NEEDLESSPARAMS);
	}
	if (!isValidNick(messageVec[1]){
		return (ERR_NOSUCHNICK);
	}

	//I left it on purpose, for me not to add it again!
	// in RFC2812: "There is no requirement that the channel, the target user is being invited to,
	//               must exist or be a valid channel."
	/*if (!isValidChannelName(messageVec[2]){
		return (ERR_NOSUCHCHANNEL);
	}*/
	return (0);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultInvite::printResult()const {

    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_inviteParamsVec.begin();
            itVec != this->_inviteParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/
