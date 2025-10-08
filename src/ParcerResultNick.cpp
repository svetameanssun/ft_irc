#include "ParcerResultNick.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultNick::ParcerResultNick()
    : AParcerResult() {
    _command = "NICK";
}
ParcerResultNick::~ParcerResultNick() {}
ParcerResultNick::ParcerResultNick(const ParcerResultNick& other): AParcerResult() {
    this->_command = other._command;
    this->_nickParamsVec = other._nickParamsVec;
    this->_command = "NICK";
};

ParcerResultNick& ParcerResultNick::operator=(const ParcerResultNick& other) {
    if(this != &other) {
        this->_nickParamsVec = other._nickParamsVec;
        this->_command = "NICK";
    }
    return (*this);
}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParcerResultNick::setParams(std::vector<std::string> nickCommand) {
    if(!nickCommand.empty()) {
        nickCommand.erase(nickCommand.begin());  // drop the first element, wich is the NICK command
    }
    this->_nickParamsVec = nickCommand;
}

const std::vector<std::string> ParcerResultNick::getNickParams(void)const {
    return (this->_nickParamsVec);
}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                   IS_VALID / IS_SPECIAL                  */
/*----------------------------------------------------------*/

bool ParcerResultNick::isSpecialChar(int c) {
    std::string specialChars = "[]\\`^{}";
    if(specialChars.find(c) == std::string::npos) {
        std::cout << "char: " << c << "\n";
        return (0);
    }
    return (1);
}

bool ParcerResultNick::isValidNick(std::vector<std::string> nickCommand) {
    std::string nickname = nickCommand.at(1);
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
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultNick::printResult()const {

    std::cout << "VECTOR:\n";
    for(std::vector<std::string>::const_iterator itVec = this->_nickParamsVec.begin();
            itVec != this->_nickParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/