#include "CommandHandler.hpp"
#include "Replies.hpp"

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

const std::vector <std::string> &CommandHandler::getValidCommands(void) const{
	return (this->validCommands);
}

std::vector<std::string>::const_iterator CommandHandler::begin() const{
	return (this->validCommands.begin());
}

std::vector<std::string>::const_iterator CommandHandler::end() const{
	return (this->validCommands.end());
}

int CommandHandler::handle(std::vector <std::string> messageVec){
		// DO IT LIKE ONE OF THER EXCERSICES IN CPP module01 ex05 !!!

	std::string cmd = messageVec.at(0);
	if (handlerMap.find(cmd) != handlerMap.end()) {
    	return (this->*handlerMap[cmd])(messageVec);
	}
	else {
    	std::cerr << "Unknown command: " << cmd << std::endl;
    return (ERR_UNKNOWNCOMMAND);
}
}
