#include "ParcerResultUser.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultUser::ParcerResultUser(): AParcerResult() {};
ParcerResultUser::ParcerResultUser(const ParcerResultUser &other): AParcerResult(){};
ParcerResultUser& ParcerResultUser::operator=(const ParcerResultUser& other){

	if (this != &other){
		this->_userParamsVec = other._userParamsVec;
	}
	return (*this);
};
ParcerResultUser::~ParcerResultUser(){};



void ParcerResultUser::setParams(std::vector<std::string> userCommand){
	
}

const std::vector<std::string> ParcerResultUser::getUserParams(void) const{
	
}



bool ParcerResultUser::isProhibitedUserChar(char c){


    std::string specialChars = "\0@\n\r ";
    if(specialChars.find(c) == std::string::npos) {
        std::cout << "char: " << c << "\n";
        return (1);
    }
    return (0);
}

int ParcerResultUser::wrongUserParams(std::vector<std::string> messageVec){
	
	if (messageVec.size() > 15)
		return (ERR_NEEDLESSPARAMS);
	if (messageVec.size() < 3)
		return (ERR_NEEDMOREPARAMS);
	for (int i = 0; i < (messageVec.at(1)).length(); i++){
		if (isProhibitedUserChar(messageVec.at(1)[i]))
			return (ERR_WRONGINPUT);
	}
	if (messageVec.at(2)[0] != ':')
		return (ERR_WRONGINPUT);
	//NUL, CR, LF
	for (int i = 2; i < messageVec.size(); i++){
		for (int j = 0; j  < messageVec.at(i).length(); j++){
			if (messageVec.at(i)[j]  == NULL || messageVec.at(i)[j]  == '\r' || messageVec.at(i)[j]  == '\n')
				return (ERR_WRONGINPUT);
		}
	}
	return (0);
}

void ParcerResultUser::printResult() const{
	
}
