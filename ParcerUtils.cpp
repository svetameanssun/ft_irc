#include "Parcer.hpp"

void Parcer::setPrefixType(pT &prefixType){
	// in the future this way I will know, 
	// who is sending the message - a server or a user
	// by default it will be PREF_USER
	prefixType = PREF_USER;
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
	setPrefixType(_prefixType);
	if (_prefixType == PREF_USER)
	{
		checkUserCommand();
	}
	else if (_prefixType == PREF_SERVER)
	{
		checkServerCommand();
	}

}