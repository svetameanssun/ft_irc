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