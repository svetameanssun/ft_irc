#include "ParcerResultNick.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultNick::ParcerResultNick()
    : AParcerResult() {
    _command = "NICK";
}

ParcerResultNick::ParcerResultNick(const ParcerResultNick& other): AParcerResult() {
    this->_command = other._command;
    this->_nickname = other._nickname;
}


ParcerResultNick& ParcerResultNick::operator=(const ParcerResultNick& other) {
    if(this != &other) {
        this->_command = other._command;
        this->_nickname = this->_nickname;
    }
    return (*this);
}

ParcerResultNick::~ParcerResultNick() {}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParcerResultNick::setParams(std::vector<std::string> nickCommand) {
    this->_nickname = nickCommand;
}

const std::string ParcerResultNick::getNickname(void)const {
    return (this->_nickname);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultNick::printResult()const {

    std::cout << "This user's nickname is:\n";
    std::cout << this->_nickname << std::endl;

}
/*==========================================================*/
