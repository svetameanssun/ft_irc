
#include "Parcer.hpp"

/**
* @brief  Method sets the flag to know who is sending the message(Operator or Client)
*
* NOW this function assigns the default Operator type.
* LATER this funtion will allow distinguishing whether the sender
* is an operator or a simple client, through accesing the client class.
*
* @param prefixType No idea what parameters will be needed to know who the sender is.
*/
/*void Parcer::setClientType(void){
	/*code to develop...
	this->isOperator = 1; //default setting
}

bool Parcer::getClientType() const{
	return (this->isOperator);
}*/


//  INVITE sveta 42

/**
* @brief Checks if the command is valid.
*
* Checks if the word written for the command is valid,
* AND that the command written corresponds to the type of the
* sender (server/user).
* To do so, parcer class has a variable that sets
* the structure pT(prefixType) to the needed value,
* so this fucntion needs to access only its own class value _prefixType.
*
* @param message Reference to a string message that is beeing sent
*			
*/
/*void Parcer::checkCommand(std::string &message){
	if (this->isOperator)
	{

	}
	else{

	}
}*/




std::vector <std::string> Parcer::customSplit(void){
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

	std::vector<std::string> messageVec;
	std::istringstream iss(_message);
	std::string temp;
	
	while(iss.good()){

		iss >> temp;
		std::cout << temp;
		messageVec.push_back(temp);
	}
	
	std::vector<std::string>::iterator ite = messageVec.end();
	/*for (std::vector<std::string>::iterator it = messageVec.begin(); it != ite; ++it)
	{
		std::cout << *it << "\n";
	}*/
	/*try{

		//checkCommand(_message);
	} catch (const std::exception &e){
		std::cerr << "input error: " << e.what();
	}*/
	
	return (messageVec);

}


int main(){
	Parcer parcer("Invite sveta 42");
	parcer.customSplit();

}