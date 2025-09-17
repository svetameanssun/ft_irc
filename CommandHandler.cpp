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

const std::vector <std::string> &CommandHandler::getValidCommands(void) const{
	return (this->validCommands);
}

std::vector<std::string>::const_iterator CommandHandler::begin() const{
	return (this->validCommands.begin());
}

std::vector<std::string>::const_iterator CommandHandler::end() const{
	return (this->validCommands.end());
}

int CommandHandler::handle(std::string command){
		// DO IT LIKE ONE OF THER EXCERSICES IN CPP module01 ex05 !!!
	if (this->_messageVec.at(0) == "PASS")
		return (handlePass(_messageVec));
	else if (this->_messageVec.at(0) == "NICK")
		return (handleNick(_messageVec));
	else if (this->_messageVec.at(0) == "USER")
		return (handleUser(_messageVec));
	else if (this->_messageVec.at(0) == "QUIT")
		return (handleQuit(_messageVec));
	else if (this->_messageVec.at(0) == "JOIN")
		return (handleJoin(_messageVec));
	else if (this->_messageVec.at(0) == "MODE")
		return (handleMode(_messageVec));
	else if (this->_messageVec.at(0) == "TOPIC")
		return (handleTopic(_messageVec));
	else if (this->_messageVec.at(0) == "INVITE")
		return (handleInvite(_messageVec));
	else if (this->_messageVec.at(0) == "KICK")
		return (handleKick(_messageVec));
	else if (this->_messageVec.at(0) == "PRIVMSG")
		return (handPrivmsg(_messageVec));
	else if (this->_messageVec.at(0) == "INFO")
		return (handleInfo(_messageVec));
}
