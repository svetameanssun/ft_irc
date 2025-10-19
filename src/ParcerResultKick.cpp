#include "ParcerResultKick.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultKick::ParcerResultKick()
    : AParcerResult() {
    _command = "Kick";
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
 */