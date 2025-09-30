#include "CommandParcer.hpp"

// MORE IDIOMATIC WAY:
CommandParcer::CommandParcer(const CommandParcer& other) : _message(other._message) {
	(void)other;
}

CommandParcer& CommandParcer::operator=(const CommandParcer& other){
	(void)other;
	return (*this);
}

std::string &CommandParcer::getMessage(void) const{
	return (this->_message);
}

std::vector<std::string> &CommandParcer::getMessageVec(void) const{
	return (this->_messageVec);
}

CommandParcer::~CommandParcer(){}
