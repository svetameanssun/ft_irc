#include "CommandHandler.hpp"


CommandHandler::CommandHandler() {

    handlerMap["PASS"] = &CommandHandler::handlePass;
    handlerMap["NICK"] = &CommandHandler::handleNick;
	handlerMap["USER"] = &CommandHandler::handleUser;
	handlerMap["QUIT"] = &CommandHandler::handleQuit;
	handlerMap["JOIN"] = &CommandHandler::handleJoin;
	handlerMap["MODE"] = &CommandHandler::handleMode;
	handlerMap["TOPIC"] = &CommandHandler::handleTopic;
	handlerMap["INVITE"] = &CommandHandler::handleInvite;
	handlerMap["KICK"] = &CommandHandler::handleKick;
	handlerMap["PRIVMSG"] = &CommandHandler::handlePrivmsg;
	handlerMap["INFO"] = &CommandHandler::handleInfo;
}

const std::map<std::string, int (CommandHandler::*)(std::vector<std::string>)>& CommandHandler::getHandlerMap() const {
    return handlerMap;
}

int CommandHandler::handle(std::vector <std::string> messageVec){
	std::string cmd = messageVec.at(0);
	if (handlerMap.find(cmd) != handlerMap.end()) {
    	return (this->*handlerMap[cmd])(messageVec);
	}
	else {
    	std::cerr << "Unknown command: " << cmd << std::endl;
    return (ERR_UNKNOWNCOMMAND);
	}
}
