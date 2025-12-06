#include "ParserResultPart.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParserResultPart::ParserResultPart()
    : AParserResult() {
    _command = "PART";
}

ParserResultPart::ParserResultPart(const ParserResultPart& other): AParserResult() {
    this->_command = other._command;
    this->_partParamsVec = other._partParamsVec;
	this->_partMessage = other._partMessage;
}


ParserResultPart& ParserResultPart::operator=(const ParserResultPart& other) {
    if(this != &other) {
        this->_partParamsVec = other._partParamsVec;
        this->_command = other._command;
		this->_partMessage = other._partMessage;
    }
    return (*this);
}

ParserResultPart::~ParserResultPart() {}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultPart::setParams(std::vector<std::string> partMessage) {
    if(!partMessage.empty()) {
        partMessage.erase(partMessage.begin());  // drop the first element (word "PART")
    }
    this->_partParamsVec.push_back(partMessage);
}

const std::vector<std::string> ParserResultPart::getPartParams(void) const{
	return (this->_partParamsVec);
}

const std::vector<std::string> ParserResultPart::getPartChannelsVec(void) const{
	return(this->_partChannelsVec);
}
const std::string ParserResultPart::getPartMessage(void) const{
	return(this->_partChannelsVec);
}
/*==========================================================*/
/*----------------------------------------------------------*/
/*                     IS_VALID_COMMAND                    */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
int ParserResultPart::checkPartMessage (std::vector<std::string> &messageVector){
	//  0      1        	2      
	// PART <channel>  [<part message>]
	if (messageVector.size() == 2){
		this->_partMessage = "default";
	}
	else if (messageVector.size() > 2){
		if (messageVector[2][0] == ':'){
			for (size_t i = 2; i < messageVector.size(); i++){
				this->_partMessage += messageVector[i];
				this->_partMessage += " ";
			}
		}
		else{
			this->_partMessage = messageVector[2];
		}
		//here we cut off the comment that we already saved in _partComment
		messageVector.resize(2);
	}
	//I am not quite sure about this condition.
	if (_partMessage.find('\r') != std::string::npos || _partMessage.find('\n') != std::string::npos){
		return (ERR_UNKNOWNCOMMAND);
	}
	
	//here we erase the ':' from the begining of the message
	//we send to the user who's leaving the chat.
	if(_partMessage.at(0) == ':'){
				_partMessage.erase(0, 1);
	}
	//erase the last space
	if(_partMessage[_partMessage.length() - 1] == ' '){
		_partMessage.erase(_partMessage.length() - 1 , 1);
	}
	//if everything is OK returns 0;
	return (0);
}

int ParserResultPart::fillPartParams(std::vector<std::string> messageVector){
	if (messageVector[1].find(',') != std::string::npos){
		_partChannelsVec = stringToVec(messageVector[1], ',');
	}
	else{
		_partChannelsVec.push_back(messageVector[1]);
	}
	for (size_t i = 0; i < _partChannelsVec.size(); i++){
		if (!isValidChanName(_partChannelsVec[i])){
			return (ERR_NOSUCHCHANNEL);
		}
	}
	//if everything is OK returns 0;
	return (0);
}

int ParserResultPart::checkPartParams(std::vector <std::string> messageVector){
	//PART <channel> *( "," <channel> ) [<Part Message>]
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	}
	int res = checkPartMessage(messageVector);
	if (res > 0) // if :trailing param exists, we will set it as _partMessageComment, if not, it will be default
	{
		return res;
	}
	//after that the _partParamsVec should already be set, without trailing params
	res = fillPartParams(messageVector);
	return (res);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                   SPLIT_AND_UNITE                        */
/*----------------------------------------------------------*/
const std::vector<std::string> ParserResultPart::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultPart::printResult()const {
   
    std::cout << "User wants to leave channel(s):\n"
	for(size_t i = 0; i < _partChannelsVec.size(); i++){
		std::cout << _partChannelsVec[i] << " " <<
	}
	std::cout << std::endl;
    std::cout << "Part message: " << this->_partMessage << std::endl;   
    
}
/*==========================================================*/

