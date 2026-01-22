#include "ParserResultNick.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParserResultNick::ParserResultNick()
    : AParserResult(), _nickname("") {
    _command = "NICK";
}

ParserResultNick::ParserResultNick(const ParserResultNick& other): AParserResult(), _nickname("") {
    this->_command = other._command;
    this->_nickname = other._nickname;
}


ParserResultNick& ParserResultNick::operator=(const ParserResultNick& other) {
    if(this != &other) {
        this->_command = other._command;
        this->_nickname = other._nickname;
    }
    return (*this);
}

ParserResultNick::~ParserResultNick() {}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParserResultNick::setParams(std::vector<std::string> nickCommand) {
    if (!_nickname.empty()){

        this->_nickname.clear();
    }
    if (!nickCommand.empty() && nickCommand.size() > 1){
        //nickCommand.erase(nickCommand.begin());
        this->_nickname = nickCommand[1];
    }
}

const std::string ParserResultNick::getNickname(void)const {
    return (this->_nickname);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultNick::printResult()const {

    std::cout << "This user's nickname is:\n";
    std::cout << this->_nickname << std::endl;

}
/*==========================================================*/