#include "Parcer.hpp"


Parcer::Parcer(const Parcer& other){
	this->_message = other._message;
}

Parcer& Parcer::operator=(const Parcer& other){
	if(this != NULL)
	{
		this->_message = other._message;
	}
	return (*this);
}

Parcer::~Parcer(){

}

std::string Parcer::getMessage(std::string message) const{
	return (message);
}