#include "CommandParcer.hpp"


void CommandParcer::splitMessage(void){
	// common message characteristics check
	if (_message.length() > 512){
		throw std::runtime_error("_message is too long\n");
	}
	if (_message.at(_message.length() - 1 ) != '\n')
	{
		throw std::runtime_error("no LF\n");
	}
	if (_message.at(_message.length() - 2) != '\r')
		throw std::runtime_error("no CR\n");

	// stpliting string into vector;
	std::istringstream iss(_message);
	std::string temp;
	while(iss >> temp){
		std::cout << temp << "\n";
		this->_messageVec.push_back(temp);
	}
}

int CommandParcer::commandProccess(void){
	std::string cmd = getMessageVec().at(0);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	this->_messageVec.at(0) = cmd;
	return (_cmdDispatcher.dispatch(_messageVec));
}

int launchParcing(void){
	std::vector<std::string> messageVec;
	CommandParcer parcer("Invite        sveta       :42  gggg  fff 			\r\n");

	try{ 
		parcer.splitMessage();
	} catch (const std::exception & e){
		std::cerr << "input error: " << e.what();
		return (666);// CHECK what ERR_VARIANT I can apply here! 
	}
	return(parcer.commandProccess());
}
