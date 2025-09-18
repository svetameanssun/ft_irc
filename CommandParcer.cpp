#include "CommandParcer.hpp"

// MORE IDIOMATIC WAY:
CommandParcer::CommandParcer(const CommandParcer& other) : _message(other._message), _isOperator(other._isOperator) {}


CommandParcer& CommandParcer::operator=(const CommandParcer& other){
	if(this != &other)
	{
		//this->_message(other._message); cannot do it, message is CONST
		this->_isOperator = other._isOperator;
	}
	return (*this);
}


/**
* @brief  Method sets the flag to know who is sending the message(Operator or Client)
*
* NOW this function assigns the default Operator type.
* LATER this funtion will allow distinguishing whether the sender
* is an operator or a simple client, through accesing the client class.
*
* @param void idea what parameters will be needed to know who the sender is.
*/
void CommandParcer::setClientType(void){
	//code to develop...
	this->_isOperator = 1; //default setting
}


bool CommandParcer::getClientType(void) const{
	return (this->_isOperator);
}

std::vector<std::string> CommandParcer::getMessageVec(void) const{
	return (this->_messageVec);
}

std::string CommandParcer::getMessage(void) const{
	return (this->_message);
}

CommandParcer::~CommandParcer(){}
