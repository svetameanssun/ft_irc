#include "Parcer.hpp"

/**
* @brief Sets the prefix type for the message sender type (SERV or USER)
*
* NOW this function assigns the default prefix type to the given reference.
* LATER this funtion will allow distinguishing whether the sender
* is a server or a user, through accesing the Server/Client class.
*
* @param prefixType Reference to a prefix type variable that will be set.
*	By default, it will be set to PREF_USER.
*/
void Parcer::setPrefixType(pT &prefixType){
	/*code to develop...*/
	prefixType = PREF_USER;
}




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
void Parcer::checkCommand(std::string &message){
	if (_prefixType == PREF_USER)
	{
		//check if the command corresponds to the list of the commands
		// of the client.
	}
	else if (_prefixType == PREF_SERVER)
	{
		// check if the command corresponds to the list of the commands
		// of the server.
	}
}




std::vector <std::string> Parcer::customSplit(){
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
	setPrefixType(_prefixType);// I set the value to default user type;
	try{
		checkCommand(_message);
	} catch (const std::exception &e){
		std::cerr << "input error: " << e.what();
	}
		

}
