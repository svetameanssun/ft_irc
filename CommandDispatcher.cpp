#include "CommandDispatcher.hpp"


CommandDispatcher::CommandDispatcher() {
    dispatcherMap["PASS"] = &CommandDispatcher::dispatchPass;
    dispatcherMap["NICK"] = &CommandDispatcher::dispatchNick;
	dispatcherMap["USER"] = &CommandDispatcher::dispatchUser;
	dispatcherMap["QUIT"] = &CommandDispatcher::dispatchQuit;
	dispatcherMap["JOIN"] = &CommandDispatcher::dispatchJoin;
	dispatcherMap["MODE"] = &CommandDispatcher::dispatchMode;
	dispatcherMap["TOPIC"] = &CommandDispatcher::dispatchTopic;
	dispatcherMap["INVITE"] = &CommandDispatcher::dispatchInvite;
	dispatcherMap["KICK"] = &CommandDispatcher::dispatchKick;
	dispatcherMap["PRIVMSG"] = &CommandDispatcher::dispatchPrivmsg;
	dispatcherMap["INFO"] = &CommandDispatcher::dispatchInfo;
}


CommandDispatcher::CommandDispatcher(const CommandDispatcher &other){
	this->dispatcherMap = other.dispatcherMap;
	this->_parcerResult = other._parcerResult;
}

CommandDispatcher&CommandDispatcher::operator=(const CommandDispatcher &other){
	if (this != &other){
		this->dispatcherMap = other.dispatcherMap;
		this->_parcerResult = other._parcerResult;
	}
	return (*this);
}

CommandDispatcher::~CommandDispatcher(){

}

const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>)>& CommandDispatcher::getDispatcherMap() const {
    return dispatcherMap;
}

int CommandDispatcher::dispatch(std::vector <std::string> messageVec){
	std::string cmd = messageVec.at(0);
	if (dispatcherMap.find(cmd) != dispatcherMap.end()) {
    	return (this->*dispatcherMap[cmd])(messageVec);
	}
	else {
    	std::cerr << "Unknown command: " << cmd << std::endl;
    return (ERR_UNKNOWNCOMMAND);
	}
}

void printMap(const std::map<std::string, std::string> &myMap) {
    if (myMap.empty())
        return;

    std::cout << "[KEY] = VALUE\n";
    for (std::map<std::string, std::string>::const_iterator it = myMap.begin();
         it != myMap.end(); ++it) {
        std::cout << "[" << it->first << "] = " << it->second << "\n";
    }
}

void printVec(const std::vector<std::string> &myVec) {
    if (myVec.empty())
        return;

    std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator it = myVec.begin();
         it != myVec.end(); ++it) {
        std::cout << *it << "\n";
    }
}
