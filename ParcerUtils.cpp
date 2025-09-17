#include "Parcer.hpp"
#include "Replies.hpp"
#include "CommandHandler.hpp"


void Parcer::splitMessage(void){
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
	while(iss.good()){

		iss >> temp;
		std::cout << temp;
		this->_messageVec.push_back(temp);
	}
}

// works with _commandList and _messageVec and ParcerFlags
//

int Parcer::commandReply(){

	/*std::vector <std::string>:: const_iterator iterBegin = _commandList.begin();
	std::vector <std::string>:: const_iterator iterEnd = _commandList.end(); 
	for (; iterBegin != iterEnd; iterBegin++){
		if (*iterBegin == message){
			return (checkParams());
		}
	}*/
	_commandList.handle(_messageVec);
}

int launchParcing(void){
	std::vector<std::string> messageVec;
	Parcer parcer("Invite        sveta       :42  gggg  fff 			");
	
	try{ 
		parcer.splitMessage();
	} catch (const std::exception & e){
		std::cerr << "input error: " << e.what();
		return (666);// CHECK what ERR_VARIANT I can apply here! 
	}
	return(parcer.commandReply());
}
