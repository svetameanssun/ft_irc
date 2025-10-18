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
}

ParcerResultUser& ParcerResultUser::operator=(const ParcerResultUser& other){

	if (this != &other){
		this->_userParamsVec = other._userParamsVec;
		this->_command = other._command;
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

	_userName.push_back('\0');
	for (size_t i = 1; i < userCommand.size(); i++)
	{
		_userName += userCommand.at(i);
	}
}

const std::vector<std::string> ParcerResultUser::getUserParams(void) const{
	return (this->_userParamsVec);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                      CHECK COMMAND                       */
/*----------------------------------------------------------*/


bool ParcerResultUser::isAllowedChar(char c){


    std::string allowedChars;
	allowedChars.push_back('\0');
	allowedChars += "@\n\r ";
    if(allowedChars.find(c) == std::string::npos) {
		
        return (true);
    }
	std::cout << "THIS " << c;
    return (false);
}

int ParcerResultUser::checkUserParams(std::vector<std::string> messageVec){
	
	if (messageVec.size() > 15)
		return (ERR_NEEDLESSPARAMS);
	if (messageVec.size() < 3)
		return (ERR_NEEDMOREPARAMS);
	std::cout << messageVec.at(1) << "\n";
	for (size_t i = 0; i < (messageVec.at(1)).length(); i++){
		bool res = isAllowedChar(messageVec.at(1)[i]);
		if (res == 0){
			return (ERR_WRONGINPUT);
		}
	}
	if (messageVec.at(2)[0] != ':')
		return (ERR_WRONGINPUT);
	//NUL, CR, LF
	for (size_t i = 2; i < messageVec.size(); i++){
		for (size_t j = 0; j  < messageVec.at(i).length(); j++){
			if (messageVec.at(i)[j]  == '\0' || messageVec.at(i)[j]  == '\r' || messageVec.at(i)[j]  == '\n')
				return (ERR_WRONGINPUT);
		}
	}
	return (0);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultUser::printResult() const{
	std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator itVec = this->_userParamsVec.begin();
        itVec != this->_userParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }
	std::cout << "FULL NAME\n";
//	std::cout << this->_userName << "\n";
}
