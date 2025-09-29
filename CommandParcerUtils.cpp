#include "CommandParcer.hpp"


int CommandParcer::splitMessage(void){
	// common message characteristics check
	if (_message.length() > 512){
		return(0);
		//throw std::runtime_error("_message is too long\n");
	}

	// the following condiions are set by US, so there is no need to check them, RIGHT??
	/*if (_message.at(_message.length() - 1 ) != '\n')
	{
		return(ERR_WRONGINPUT);
		//throw std::runtime_error("no LF\n");
	}
	if (_message.at(_message.length() - 2) != '\r')
	{
		return(ERR_WRONGINPUT);
		//throw std::runtime_error("no CR\n");
	}*/

	// spliting string into vector;
	std::istringstream iss(_message);
	std::string temp;
	while(iss >> temp){
		//std::cout << temp << "\n";
		this->_messageVec.push_back(temp);
	}
	return (1);
}

int CommandParcer::commandProccess(void){
	std::string cmd = getMessageVec().at(0);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	this->_messageVec.at(0) = cmd;
	return (_cmdDisp.dispatch(_messageVec));
}

int launchParcing(void){
	std::vector<std::string> messageVec;
	//CommandParcer parcer("JOIN        sveta       :42  gggg  fff 			\r\n");
	CommandParcer parcer("JOIN        chan1,chan2,chan3,chan4       11,22,33,11  ");

	if (!parcer.splitMessage()){
		return (ERR_WRONGINPUT);// CHECK what ERR_VARIANT I can apply here! 
	}
	return(parcer.commandProccess());
}






