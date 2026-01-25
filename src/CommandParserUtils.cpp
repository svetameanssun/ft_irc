#include "CommandParser.hpp"

bool CommandParser::splitMessage(void){
	// common message characteristics check
	_messageVec.clear();
	if (_message.length() > 512){
		return(0);
	}
	// spliting string into vector;
	std::istringstream iss(_message);
	std::string temp;
	while(iss >> temp){
		this->_messageVec.push_back(temp);
	}
	return (1);
}

int CommandParser::commandProccess(void){

	if (_messageVec.empty()){
    	return ERR_UNKNOWNCOMMAND;
	}
	std::string cmd = getMessageVec().at(0);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	this->_messageVec.at(0) = cmd;
	int res = _cmdDisp.dispatch(_messageVec);
	this->_wrongInput = _cmdDisp.getFlagMal();
	return (res);
}
