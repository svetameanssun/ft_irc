
    ParcerResultPart();
    ParcerResultPart(const ParcerResultPart &other);
    ParcerResultPart &operator=(const ParcerResultPart &other);
    virtual ~ParcerResultPart();

    /*================= SETTERS / GETTERS ===============*/
    void setParams(std::vector<std::string> partCommand);
    const std::vector<std::string> getPartParams(void) const;
    const std::vector<std::string> getPartChannelsVec(void) const;
    
    /*================= VALIDATION ======================*/
    //bool isValidChanNameChar(int c);
    //bool isValidChanName(std::string channelName);

    //bool isSpecialChar(int c);
    //bool isValidNick(std::string nickname);

    /*================= COMMAND CHECKING ================*/
    int checkPartMessage(std::vector<std::string> &messageVector);
    int fillPartParams(std::vector<std::string> messageVector);
    int checkPartParams(std::vector<std::string> messageVector);

    /*================= HELPERS =========================*/
    const std::vector<std::string> stringToVec(std::string str, char delim);

    /*================= DEBUG / OUTPUT ==================*/
    void printResult(void) const;
private:
    std::vector<std::string> _partParamsVec;   // Stores raw parameters (after "PART")
    std::vector <std::string> _partChannelsVec;// channels in order (the channels the user is leaving)
    std::string _partMessage;  


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
	return (_partParamsVec);
}

const std::vector<std::string> getKickChannelsVec(void) const{
	return(this->_kickChannelsVec);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                     IS_VALID_COMMAND                    */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
int  ParcerResultKick::checkKickComment (std::vector<std::string> &messageVector){
	for(int i = 0; i < messageVector.size(); i++){
		if (messageVector[i].find(':') != std::string::npos)
			break;
	}
	if (i == messageVector.size() && i == 3){
		this->_kickComment = "default";
	}
	else if (i == messageVector.size() && i > 3){
		this->_kickComment = messageVector[3];
	}
	else{
		int save_i = i;
		for (; i < messageVector.size(); i++){
			this->_kickComment += messageVector[i];
		}
		//here we cut off the comment that we already saved in _kickComment
		messageVector.resize(save_i + 1);
	}
	//I am not quite sure about this condition.
	if (_kickComment.find('\r') != std::string::npos || _kickComment.find('\n') != std::string::npos){
		return (ERR_UNKNOWNCOMMAND);
	}
	
	//here we erase the ':' from the begining of the message
	//we send to the kicked out user.
	if(_kickComment.at(0) == ':'){
				_kickComment.erase(0, 1);
	}
	//if everything is OK returns 0;
	return (0);
}

int  ParcerResultKick::fillKickParams(std::vector<std::string> messageVector){
	
	if (messageVector[1].find(',') != std::string::npos){
		_kickChannelsVec = stringToVec(messageVector[1], ',');
	}
	else{
		_kickChannelsVec.push_back(messageVector[1]);
	}
	if (messageVector[2].find(',') != std::string::npos){
		_kickUsersVec = stringToVec(messageVector[2], ',');
	}
	else{
		_kickUsersVec.push_back(messageVector[2]);
	}
	if (_kickChannelsVec.size() != 1 && _kickChannelsVec.size() != _kickUsersVec.size()){
		return (ERR_NEEDLESSPARAMS);
	}
	for (size_t i = 0; i < _kickUsersVec.size(); i++){
		if (!isValidNick(_kickUsersVec[i])){
			return (ERR_UNKNOWNCOMMAND);
		}
		if (i < _kickChannelsVec.size()){
			if (!isValidChanName(_kickChannelsVec[i])){
				return (ERR_NOSUCHCHANNEL);
			}
		}
	}
	this->_kickParamsMap = vectorsToMap(_kickChannelsVec, _kickUsersVec);
	//if everything is OK returns 0;
	return (0);
}

int ParcerResultKick::checkKickParams(std::vector <std::string> messageVector){
	if (messageVector.size() <= 2){
		return (ERR_NEEDMOREPARAMS);
	}
	int res = checkKickComment(messageVector);
	if (res > 0); // if :trailing param exists, we will set it as _kickComment, if not, it will be default
	// setKickComment also checks if the trailing comment is valid{
		return res;
	}
	//after that the _kickParamsVec should already be set, without trailing params
	res = fillKickParams(messageVector);
	return (res);
}
/*==========================================================*/

/*----------------------------------------------------------*/
/*                   SPLIT_AND_UNITE                        */
/*----------------------------------------------------------*/
const std::vector<std::string> ParcerResultKick::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

std::map<int, std::vector<std::string>> ParcerResultKick::vectorsToMap(std::vector<std::string> channels, std::vector<std::string>users){
	std::map <int, std::vector<std::string>> map;
	if (channels.size() == 1 && users.size() == 1){
		map[0].push_back(channels[0]);
        map[0].push_back(users[0]);
	}
	else if (channels.size() == 1){
		for (size_t i = 0; i < users.size(); ++i){
			map[i].push_back(channels[0]);
			map[i].push_back(users[i]);
		}
	}
	else{
		for (size_t i = 0; i < users.size(); ++i){
			map[i].push_back(channels[i]);
			map[i].push_back(users[i]);
		}
	}
	return map;
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultKick::printResult()const {
   
    for (std::map<std::string, std::vector<std::string> >::const_iterator it = _kickParamsMap.begin();
     it != _kickParamsMap.end();
     ++it)
	{
    std::cout << "CHANNEL: " << it->second.at(0) << std::endl;   
    std::cout << "USER: "    << it->second.at(1) << std::endl;
    std::cout << std::endl;
	}

}
/*==========================================================*/

