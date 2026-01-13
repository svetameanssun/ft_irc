#include "CommandDispatcher.hpp"

CommandDispatcher::CommandDispatcher() {
    dispatcherMap["PASS"] = &CommandDispatcher::dispatchPass;
    dispatcherMap["NICK"] = &CommandDispatcher::dispatchNick;
	dispatcherMap["USER"] = &CommandDispatcher::dispatchUser;
	dispatcherMap["JOIN"] = &CommandDispatcher::dispatchJoin;
	dispatcherMap["QUIT"] = &CommandDispatcher::dispatchQuit;
	dispatcherMap["MODE"] = &CommandDispatcher::dispatchMode;
	dispatcherMap["TOPIC"] = &CommandDispatcher::dispatchTopic;
	dispatcherMap["INVITE"] = &CommandDispatcher::dispatchInvite;
	dispatcherMap["KICK"] = &CommandDispatcher::dispatchKick;
	dispatcherMap["PRIVMSG"] = &CommandDispatcher::dispatchPrivmsg;
	dispatcherMap["PART"] = &CommandDispatcher::dispatchPart;
	dispatcherMap["QUIT"] = &CommandDispatcher::dispatchQuit;
	dispatcherMap["NOTICE"] = &CommandDispatcher::dispatchNotice;
}


CommandDispatcher::CommandDispatcher(const CommandDispatcher &other){
	this->dispatcherMap = other.dispatcherMap;
	this->_parserResult = other._parserResult;
}

CommandDispatcher&CommandDispatcher::operator=(const CommandDispatcher &other){
	if (this != &other){
		this->dispatcherMap = other.dispatcherMap;
		this->_parserResult = other._parserResult;
	}
	return (*this);
}

CommandDispatcher::~CommandDispatcher(){
	delete (_parserResult);
}

const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>&)>& CommandDispatcher::getDispatcherMap() const {
    return dispatcherMap;
}

int CommandDispatcher::dispatch(std::vector <std::string> &messageVec){
	std::string cmd = messageVec.at(0);
	if (dispatcherMap.find(cmd) != dispatcherMap.end()) {
    	return ((this->*dispatcherMap[cmd])(messageVec));
	}
	else {
    	std::cerr << "Unknown command: " << cmd << std::endl;
    return (ERR_UNKNOWNCOMMAND);
	}
}

void CommandDispatcher::createParserResult(std:: string rawCommand){
	
}


AParserResult *CommandDispatcher::getParserResult() const { return this->_parserResult; }