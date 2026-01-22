#include "CommandParser.hpp"

// MORE IDIOMATIC WAY:
CommandParser::CommandParser(const std::string &message)
    : _message(message) {}

CommandParser::CommandParser(const CommandParser& other) : _message(other._message) {
	(void)other;
}

CommandParser& CommandParser::operator=(const CommandParser& other){
	(void)other;
	return (*this);
}

const std::string &CommandParser::getMessage(void) const{
	return (_message);
}

const std::vector<std::string> &CommandParser::getMessageVec(void) const{
	return (_messageVec);
}

const CommandDispatcher &CommandParser::getCommandDispatcher() const { return this->_cmdDisp; }

CommandParser::~CommandParser(){}

