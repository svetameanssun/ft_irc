#include "CommandDispatcher.hpp"

CommandDispatcher::CommandDispatcher() : _parserResult(NULL), _flagMal(false){
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
	dispatcherMap["NOTICE"] = &CommandDispatcher::dispatchNotice;
}


/*CommandDispatcher::CommandDispatcher(const CommandDispatcher &other){
	this->dispatcherMap = other.dispatcherMap;
	this->_parserResult = other._parserResult;
}

CommandDispatcher&CommandDispatcher::operator=(const CommandDispatcher &other){
	if (this != &other){
		this->dispatcherMap = other.dispatcherMap;
		this->_parserResult = other._parserResult;
	}
	return (*this);
}*/

CommandDispatcher::~CommandDispatcher(){
	delete (_parserResult);
}

bool CommandDispatcher::getFlagMal() const{
	return (_flagMal);
}

void CommandDispatcher::createParserResult(std::string &command){
	delete (_parserResult);
	if (command == "PASS"){
		this->_parserResult = new ParserResultPass();
	}
	else if (command == "NICK"){
		this->_parserResult = new ParserResultNick();
	}
	else if (command == "USER"){
		this->_parserResult = new ParserResultUser();
	}
	else if (command == "JOIN"){
		this->_parserResult = new ParserResultJoin();
	}
	else if (command == "QUIT"){
		this->_parserResult = new ParserResultQuit();
	}
	else if (command == "MODE"){
		this->_parserResult = new ParserResultMode();
	}
	else if (command == "TOPIC"){
		this->_parserResult = new ParserResultTopic();
	}
	else if (command == "INVITE"){
		this->_parserResult = new ParserResultInvite();
	}
	else if (command == "KICK"){
		this->_parserResult = new ParserResultKick();
	}
	else if (command == "PRIVMSG"){
		this->_parserResult = new ParserResultPrivmsg();
	}
	else if (command == "PART"){
		this->_parserResult = new ParserResultPart();
	}
	else if (command == "NOTICE"){
		this->_parserResult = new ParserResultNotice();
	}
	else{
		_flagMal = true;
	}
}

const std::map<std::string, int (CommandDispatcher::*)(std::vector<std::string>&)>& CommandDispatcher::getDispatcherMap() const {
    return dispatcherMap;
}

int CommandDispatcher::dispatch(std::vector <std::string> &messageVec){
	if (messageVec.empty()){
		return (ERR_UNKNOWNCOMMAND);
	}
	std::string cmd = messageVec.at(0);
    createParserResult(cmd);

	if (!_parserResult){
    	return ERR_UNKNOWNCOMMAND;
	}
	if (dispatcherMap.find(cmd) != dispatcherMap.end()) {
    	return ((this->*dispatcherMap[cmd])(messageVec));
	}
	else {
    	std::cerr << "Unknown command: " << cmd << std::endl;
    	return (ERR_UNKNOWNCOMMAND);
	}
}

AParserResult *CommandDispatcher::getParserResult() const { return this->_parserResult; }
