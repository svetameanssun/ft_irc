#include "ParserResultUser.hpp"

// [RUBEN] - changed _nickname to _username here, because it is how it should be !
// change in your code not to mix up  _nickname that we set with the command NICK
// and this _username (which for SOME REASON i also wrongly named _nickname, now here it is _username
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
	this->_username = other._username;
}

ParserResultUser& ParserResultUser::operator=(const ParserResultUser& other){

	if (this != &other){
		this->_userParamsVec = other._userParamsVec;
		this->_command = other._command;
		this->_realname = other._realname;
		this->_username = other._username;
	}
	return (*this);
}
ParserResultUser::~ParserResultUser(){}


/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/
void ParserResultUser::setParams(std::vector<std::string> userCommand){
	this->_userParamsVec.clear(); //[SVETA] does it work?
    this->_username.clear();
  	if (!userCommand.empty() && userCommand.size() > 1) {
    	userCommand.erase(userCommand.begin());  // drop the first element, which is the command
  	}
	if (!userCommand.empty()){
  		this->_userParamsVec = userCommand;
		this->_username = userCommand[0];
	}
	
}

void ParserResultUser::setRealname(std::string name){
	this->_realname = name;
}

const std::vector<std::string> ParserResultUser::getUserParams(void) const{
	return (this->_userParamsVec);
}

const std::string ParserResultUser::getRealname(void) const{
	return (this->_realname);
}

const std::string ParserResultUser::getUsername(void) const{
	return (this->_username);
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

bool ParserResultUser::isAllowedNumber(std::string number){
	size_t i = 0;
	while(number[i] && number[i]== '+'){
		i++;
	}
	if(!number[i]){
		return (false);
	}
	if (number[i] == '-'){
		return (false);
	}
	for(;i < number.length(); i++){
		if(!std::isdigit(number[i])){
			return (false);
		}
	}
	return (true);
}

int ParserResultUser::checkUserParams(std::vector<std::string> messageVec){
	
	//check username
	for(size_t i = 0; i < messageVec[1].length(); i++){
		if (!isAllowedChar(messageVec[1][i])){
				return (ERR_WRONGINPUT);
		}
	}
	this->_realname.clear();
	// 
	// USER guest   0       *     :Ronnie Reagan
	// USER guest :Ronnie Reagan
	//  0    1        2      3      4       5
	std::string name;
	size_t i = 2;
	if (messageVec.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	}
	if (isAllowedNumber(messageVec.at(2))){
		if (messageVec.at(3) != "*"){
			return (ERR_WRONGINPUT);
		}
		if (messageVec.size() < 5){
			return (ERR_NEEDMOREPARAMS);
		}
		i = 4;
	}
	if (messageVec[i][0]!= ':'){
		name+=messageVec.at(i);
	}
	else{
		for (; i < messageVec.size(); i++){
			name += messageVec.at(i);
			name += " ";
		}
	}
	if(!name.empty() && name[0] == ':'){
		name.erase(0, 1);
	}
	if(!name.empty() && name.at(name.length() - 1) == ' '){
		name.erase(name.length() - 1, 1);
	}
	setRealname(name);
	return (0);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultUser::printResult() const{
	std::cout << this->_username << "'s real name is" << std::endl;
    std::cout << this->_realname << std::endl;
}
