#include "ParcerResultPart.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultPart::ParcerResultPart()
    : AParcerResult() {
    _command = "PART";
}

ParcerResultPart::ParcerResultPart(const ParcerResultPart& other): AParcerResult() {
    this->_command = other._command;
    this->_partParamsVec = other._partParamsVec;
}


ParcerResultPart& ParcerResultPart::operator=(const ParcerResultPart& other) {
    if(this != &other) {
        this->_partParamsVec = other._partParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultPart::~ParcerResultPart() {}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultPart::setParams(std::vector<std::string> partCommand) {
    if(!partCommand.empty()) {
        partCommand.erase(partCommand.begin());  // drop the first element (word "PART")
    }
    this->_partParamsVec = partCommand;
}

const std::vector<std::string> ParcerResultPart::getPartParams(void) const{
	return (this->_partParamsVec);
}

const std::vector<std::string> getPartChannelsVec(void) const{
	return(this->_partChannelsVec);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                     IS_VALID_COMMAND                    */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
int  ParcerResultPart::checkPartComment (std::vector<std::string> &messageVector){
	//  0      1        	2      
	// PART <channel>  [<part message>]
	if (messageVector.size() == 2){
		this->_partComment = "default";
	}
	else if (messageVector.size() > 2){
		if (messageVector[2][0] == ':'){
			for (size_t i = 2; i < messageVector.size(); i++){
				this->_partComment += messageVector[i];
				this->_partComment += " ";
			}
		}
		else{
			this->_partComment = messageVector[2];
		}
		//here we cut off the comment that we already saved in _partComment
		messageVector.resize(2);
	}
	//I am not quite sure about this condition.
	if (_partComment.find('\r') != std::string::npos || _partComment.find('\n') != std::string::npos){
		return (ERR_UNKNOWNCOMMAND);
	}
	
	//here we erase the ':' from the begining of the message
	//we send to the kicked out user.
	if(_partComment.at(0) == ':'){
				_partComment.erase(0, 1);
	}
	//erase the last space
	_partComment.erase(_partComment.length() - 1 , 1);
	//if everything is OK returns 0;
	return (0);
}

int  ParcerResultPart::fillPartParams(std::vector<std::string> messageVector){
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

int ParcerResultPart::checkPartParams(std::vector <std::string> messageVector){
	//PART <channel> *( "," <channel> ) [<Part Message>]
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	}
	int res = checkPartMessage(messageVector);
	if (res > 0) // if :trailing param exists, we will set it as _partMessageComment, if not, it will be default
	// setPartComment also checks if the trailing comment is valid{
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
const std::vector<std::string> ParcerResultPart::stringToVec(std::string str, char delim) {
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

void ParcerResultPart::printResult()const {
   
    std::cout << "User wants to leave channel(s):\n"
	for(size_t i = 0; i < _partChannelsVec.size(); i++){
		std::cout << _partChannelsVec[i] << " " <<
	}
	std::cout << std::endl;
    std::cout << "Part message: " << this->_partMessage << std::endl;   
    
}
/*==========================================================*/

