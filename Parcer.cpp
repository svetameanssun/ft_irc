#include "Parcer.hpp"

// MORE IDIOMATIC WAY:
Parcer::Parcer(const Parcer& other) : _message(other._message), _isOperator(other._isOperator) {}


Parcer& Parcer::operator=(const Parcer& other){
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
void Parcer::setClientType(void){
	//code to develop...
	this->_isOperator = 1; //default setting
}


bool Parcer::getClientType(void) const{
	return (this->_isOperator);
}

std::vector<std::string> Parcer::getMessageVec(void) const{
	return (this->_messageVec);
}

std::string Parcer::getMessage(void) const{
	return (this->_message);
}

Parcer::~Parcer(){}