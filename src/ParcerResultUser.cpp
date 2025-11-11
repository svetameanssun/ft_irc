#include "ParcerResultUser.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultUser::ParcerResultUser(): AParcerResult() {
	_command = "USER";
}

ParcerResultUser::ParcerResultUser(const ParcerResultUser &other): AParcerResult(){
	this->_userParamsVec = other._userParamsVec;
	this->_command = other._command;
	this->_realname = other._realname;
	this->_nickname = other._nickname;
}

ParcerResultUser& ParcerResultUser::operator=(const ParcerResultUser& other){

	if (this != &other){
		this->_userParamsVec = other._userParamsVec;
		this->_command = other._command;
		this->_realname = other._realname;
		this->_nickname = other._nickname;
	}
	return (*this);
}
ParcerResultUser::~ParcerResultUser(){}


/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParcerResultUser::setParams(std::vector<std::string> userCommand){
	if (!userCommand.empty()) {
    	userCommand.erase(userCommand.begin());  // drop the first element, which is the command
  	}
  	this->_userParamsVec = userCommand;

	//_realname.push_back('\0'); not sure if it is needed.
	this->_nickname += userCommand.at(0); 
	if (userCommand.at(2)[0]!= ':'){
		_realname+=userCommand.at(2);
	}
	else{
		for (size_t i = 1; i < userCommand.size(); i++){
			_realname += userCommand.at(i);
		}
	}
	if(_realname.at(0) == ':'){
		_realname.erase(0, 1);
	}
}

const std::vector<std::string> ParcerResultUser::getUserParams(void) const{
	return (this->_userParamsVec);
}

const std::string ParcerResultUser::getRealname(void) const{
	return (this->_realname);
}

const std::string ParcerResultUser::getNickname(void) const{
	return (this->_nickname);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                      CHECK COMMAND                       */
/*----------------------------------------------------------*/

bool ParcerResultUser::isAllowedChar(char c){
    std::string prohibitedChars;
	//prohibitedChars.push_back('\0');
	prohibitedChars += "@\n\r ";
    if(prohibitedChars.find(c) == std::string::npos) {
		//if we HAVEN'T find c in prohibitedChars ->retrun true
        return (true);
    }
    return (false);
}

int ParcerResultUser::checkUserParams(std::vector<std::string> messageVec){
	
	if (messageVec.size() > 15)
		return (ERR_NEEDLESSPARAMS);
	if (messageVec.size() < 3)
		return (ERR_NEEDMOREPARAMS);
	//NUL, CR, LF, space
	for (size_t i = 2; i < messageVec.size(); i++){
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

void ParcerResultUser::printResult() const{
	std::cout << this->_nickname << "'s real name is" << std::endl;
    std::cout << this->_realname << std::endl;
}
