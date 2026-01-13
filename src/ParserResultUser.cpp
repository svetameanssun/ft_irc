#include "ParserResultUser.hpp"

//TODO: [LANA]: It seems like the parser does not get correctly the real name
// my parser has to accept this:
// USER guest 0 * :Ronnie Reagan
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultUser::ParserResultUser(): AParserResult() {
	_command = "USER";
}

ParserResultUser::ParserResultUser(const ParserResultUser &other): AParserResult(){
	this->_userParamsVec = other._userParamsVec;
	this->_command = other._command;
	this->_realname = other._realname;
	this->_nickname = other._nickname;
}

ParserResultUser& ParserResultUser::operator=(const ParserResultUser& other){

	if (this != &other){
		this->_userParamsVec = other._userParamsVec;
		this->_command = other._command;
		this->_realname = other._realname;
		this->_nickname = other._nickname;
	}
	return (*this);
}
ParserResultUser::~ParserResultUser(){}


/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParserResultUser::setParams(std::vector<std::string> userCommand){
	if (!userCommand.empty()) {
    	userCommand.erase(userCommand.begin());  // drop the first element, which is the command
  	}
  	this->_userParamsVec = userCommand;
	// guest 0 * :Ronnie Reagan
	//_realname.push_back('\0'); //not sure if it is needed.
	this->_nickname += userCommand.at(0);
	
	size_t i = 1;
	if (userCommand.size() >= 4 && userCommand.at(1) == "0" && userCommand.at(2) == "*"){
		i = 3;
	}

	if (userCommand.at(i)[0]!= ':'){
		_realname+=userCommand.at(i);
	}
	else{
		for (; i < userCommand.size(); i++){
			_realname += userCommand.at(i);
			_realname += " ";
		}
	}
	if(_realname.at(0) == ':'){
		_realname.erase(0, 1);
	}
	std::cout << "=============================================" + _realname;
	if(_realname.at(_realname.length() - 1) == ' '){
		_realname.erase(_realname.length() - 1, 1);
	}
}

const std::vector<std::string> ParserResultUser::getUserParams(void) const{
	return (this->_userParamsVec);
}

const std::string ParserResultUser::getRealname(void) const{
	return (this->_realname);
}

const std::string ParserResultUser::getNickname(void) const{
	return (this->_nickname);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                      CHECK COMMAND                       */
/*----------------------------------------------------------*/

bool ParserResultUser::isAllowedChar(char c){
    std::string prohibitedChars;
	//prohibitedChars.push_back('\0');
	prohibitedChars += "@\n\r ";
    if(prohibitedChars.find(c) == std::string::npos) {
		//if we HAVEN'T find c in prohibitedChars ->retrun true
        return (true);
    }
    return (false);
}

int ParserResultUser::checkUserParams(std::vector<std::string> messageVec){
	//TODO: [LANA]: It seems like the parser does not get correctly the real name
	// my parser has to accept this:
	
	if (messageVec.size() > 15){
		return (ERR_NEEDLESSPARAMS);
	}
	if (messageVec.size() < 3){
		return (ERR_NEEDMOREPARAMS);
	}
	size_t i = 2;
	
	if (messageVec.size() >= 5 && messageVec.at(2) == "0" && messageVec.at(3) == "*"){
		i = 4;
	}
	//NUL, CR, LF, space
	for (; i < messageVec.size(); i++){
		for (size_t j = 0; j  < messageVec.at(i).length(); j++){
			if (!isAllowedChar(messageVec.at(i)[j]))
				return (ERR_WRONGINPUT);
		}
	}
	return (0);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultUser::printResult() const{
	std::cout << this->_nickname << "'s real name is" << std::endl;
    std::cout << this->_realname << std::endl;
}