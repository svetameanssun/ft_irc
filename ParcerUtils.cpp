#include "Parcer.hpp"

/**
* @brief  Method sets the flag to know who is sending the message(Operator or Client)
*
* NOW this function assigns the default Operator type.
* LATER this funtion will allow distinguishing whether the sender
* is an operator or a simple client, through accesing the client class.
*
* @param void idea what parameters will be needed to know who the sender is.
*/
void Parcer::setClientType(void){
	//code to develop...
	this->isOperator = 1; //default setting
}

/**
* @brief  Method checks the flag to know who is sending the message(Operator or Client)
*
* The function returns bool value: true is the sender who's message is being analysed
* is operator, and false if it is a simple client
*
* @param void idea what parameters will be needed to know who the sender is.
*/
bool Parcer::getClientType(void) const{
	return (this->isOperator);
}

/**
* @brief Checks if the command is valid.
*
* Checks if the word written for the command is valid,
* AND that the command written corresponds to the type of the
* sender (operator/client).
* To do so, parcer class has a variable that sets
* the bool flag  isOperator to the needed value,
* so this fucntion needs to access only its own class value isOperator.
*
* @param message Reference to a string message that is beeing sent
*			
*/
bool Parcer::isValidCommand(std::string &message){
	
	



	if (!this->isOperator)
	{
		if (message == "KICK"
			||  message == "INVITE"
			|| message == "TOPIC"
			|| message == "MODE"){
				return (false)
		}

	}
	
}


bool Parcer::isValidParam(std::vector<std::string> &messageVec){
	
}





std::vector <std::string> Parcer::splitMessage(std::vector<std::string> &messageVec){
	// common message characteristics check
	try{
	if (_message.length() > 512){
		throw std::runtime_error("_message is too long\n");
	}
	if (_message.at(_message.length() - 1 ) != '\n')
	{
		throw std::runtime_error("no LF\n");
	}
	if (_message.at(_message.length() - 2) != '\r')
		throw std::runtime_error("no CR\n");
	}
	catch (const std::exception & e){
		std::cerr << "input error: " << e.what();
	}
	// stpliting string into vector;
	std::istringstream iss(_message);
	std::string temp;
	while(iss.good()){

		iss >> temp;
		std::cout << temp;
		messageVec.push_back(temp);
	}
	return (messageVec);
}

bool Parcer::isCommonCommand(std::string message){
	std::vector <std::string>:: const_iterator itBegin = this->commandVec.begin();
	std::vector <std::string>::const_iterator itEnd = this->commandVec.end();
	for (; itBegin!= itEnd; itBegin++){
		if (*itBegin ==)
	}
}


bool Parcer::isOperatorComamnd(std::string message){

}
