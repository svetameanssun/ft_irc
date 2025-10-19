#include "ParcerResultPrivmsg.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultPrivmsg::ParcerResultPrivmsg()
    : AParcerResult() {
    _command = "Privmsg";
}

ParcerResultPrivmsg::ParcerResultPrivmsg(const ParcerResultPrivmsg& other): AParcerResult() {
    this->_command = other._command;
    this->_privmsgParamsVec = other._privmsgParamsVec;
}


ParcerResultPrivmsg& ParcerResultPrivmsg::operator=(const ParcerResultPrivmsg& other) {
    if(this != &other) {
        this->_privmsgParamsVec = other._privmsgParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultPrivmsg::~ParcerResultPrivmsg() {}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultPrivmsg::setParams(std::vector<std::string> privmsgCommand) {
    if(!privmsgCommand.empty()) {
        privmsgCommand.erase(privmsgCommand.begin());  // drop the first element, wich is the privmsg command
    }
    this->_privmsgParamsVec = privmsgCommand;
}

const std::vector<std::string> ParcerResultPrivmsg::getPrivmsgParams(void) const{
	return (_privmsgParamsVec);
}


/*==========================================================*/

/*----------------------------------------------------------*/
/*                   IS_VALID / IS_SPECIAL                  */
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultPrivmsg::printResult()const {

    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_privmsgParamsVec.begin();
            itVec != this->_privmsgParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/