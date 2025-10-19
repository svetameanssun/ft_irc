#include "CommandParcer.hpp"

bool CommandParcer::splitMessage(void){
	// common message characteristics check
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

int CommandParcer::commandProccess(void){
	std::string cmd = getMessageVec().at(0);
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	this->_messageVec.at(0) = cmd;
	//std::cout << _messageVec.at(0);
	//std::cout << _message;
	return (_cmdDisp.dispatch(_messageVec));
}

//int launchParcing(std::string messageStr){
//	// string OUTSIDE the functions.
//	//std::string messageStr;
//
//
//	//messageStr = "JOIN        sveta       :42  gggg  fff 			\r\n";
//	//messageStr = "JOIN        chan1,chan2,chan3,chan4       11,22,33,11  ";
//	//messageStr = "JOIN newChannel";
//	//messageStr = "JOIN #newChannel";
//	//messageStr = "JOIN #newChannel,&anotherChannel,#wonderfulChannel,&a,&b 1234,9999,0000";
//	//messageStr = "JOIN #newChannel,&anotherChannel,#wonderfulChannel,&a,&b 1234,9999,0000,8,9,7,6,5,4";
//	//messageStr = "Join newChan"; // does not start with & or #
//	//messageStr = "Join &newChan"; // OK
//	//messageStr = "NICK newNick";
//	//messageStr = "NICK newNickname"; //  nickname no longer than 9 chars (?)
//	//messageStr = "NICK 1392r"; //  nickname cannotstart with digit
//	//messageStr = "user newNickname"; // not enough parameters
//	//messageStr = "user newNickname  dddd dddd"; // wrong input
//	//messageStr = "user newNickname  dddd:dddd"; // wrong input
//	//messageStr = "USER n@ewNickname :Hello world"; // wrong input 
//	//messageStr = "USeR $newNickname :My Full NAME 37R98YWEE409WRUSC[-fp;t9E";
//	
//
//	
//
//	
//
//	CommandParcer parcer(messageStr);
//	if (!parcer.splitMessage()){
//		std::cout << "THIS";
//
//		return (ERR_WRONGINPUT);// CHECK what ERR_VARIANT I can apply here! 
//	}
//	
//	int result = parcer.commandProccess();//
//	this->_parcerResult = parcer.getCommandDispatcher().getParcerResult();
//	return (result);
//}






