#include "CommandParcer.hpp"

// MORE IDIOMATIC WAY:
CommandParcer::CommandParcer(const CommandParcer& other) : _message(other._message) {}


CommandParcer& CommandParcer::operator=(const CommandParcer& other){
	return (*this);
}


std::vector<std::string> CommandParcer::getMessageVec(void) const{
	return (this->_messageVec);
}

std::string CommandParcer::getMessage(void) const{
	return (this->_message);
}

CommandParcer::~CommandParcer(){}
