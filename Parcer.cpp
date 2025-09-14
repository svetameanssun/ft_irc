#include "Parcer.hpp"


/*Parcer::Parcer(const Parcer& other){
	this->_message = other._message;
}*/

// MORE IDIOMATIC WAY:
Parcer::Parcer(const Parcer& other) : _message(other._message), isOperator(other.isOperator) {}


Parcer& Parcer::operator=(const Parcer& other){
	if(this != &other)
	{
		this->_message = other._message;
		isOperator = other.isOperator;
	}
	return (*this);
}

Parcer::~Parcer(){

}

std::string Parcer::getMessage(void) const{
	return (this->_message);
}