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

void CommandHandler::handle(std::string command){
		// DO IT LIKE ONE OF THER EXCERSICES IN CPP module01 ex05 !!!
	if (this->_messageVec.at(0) == "PASS")
		handlePass(_messageVec);
	else if (this->_messageVec.at(0) == "NICK")
		handleNick(_messageVec);
	else if (this->_messageVec.at(0) == "USER")
		handleUser(_messageVec);
	else if (this->_messageVec.at(0) == "QUIT")
		handleQuit(_messageVec);
	else if (this->_messageVec.at(0) == "JOIN")
		handleJoin(_messageVec);
	else if (this->_messageVec.at(0) == "MODE")
		handleMode(_messageVec);
	else if (this->_messageVec.at(0) == "TOPIC")
		handleTopic(_messageVec);
	else if (this->_messageVec.at(0) == "INVITE")
		handleInvite(_messageVec);
	else if (this->_messageVec.at(0) == "KICK")
		handleKick(_messageVec);
	else if (this->_messageVec.at(0) == "PRIVMSG")
		handPrivmsg(_messageVec);
	else if (this->_messageVec.at(0) == "INFO")
		handleInfo(_messageVec);
}