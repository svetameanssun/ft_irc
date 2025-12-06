#include "ParcerResultNotice.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultNotice::ParcerResultNotice()
    : AParcerResult(){
        _command = "NOTICE";
}

ParcerResultNotice::ParcerResultNotice(const ParcerResultNotice &other){
    this->_command = other._command;
    this->_noticeParamsVec = other._noticeParamsVec;
    this->_targetVec = other._targetVec;
}

ParcerResultNotice& ParcerResultNotice::operator=(const ParcerResultNotice& other){
    if(this != &other) {
        this->_noticeParamsVec = other._noticeParamsVec;
        this->_targetVec = other._targetVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultNotice::~ParcerResultNotice(){}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultNotice::setParams(std::vector<std::string> noticeCommand) {
  if (!noticeCommand.empty()) {
    noticeCommand.erase(noticeCommand.begin());  // drop the first element, which is the command
  }
  this->_noticeParamsVec = noticeCommand;
}

const std::vector<std::string> ParcerResultNotice::getNoticeParams(void) const {
  return (this->_noticeParamsVec);
}

const std::vector<std::string> ParcerResultNotice::getTargetVec(void) const {
  return (this->_targetVec);
}

const std::string ParcerResultNotice::getNoticeMessage(void) const {
  return (this->_noticeMessage);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                        SPLIT                             */
/*----------------------------------------------------------*/
const std::vector<std::string> ParcerResultNotice::stringToVec(std::string str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while(getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                       IS_VALID_PARAM                      */
/*----------------------------------------------------------*/
int ParcerResultNotice::checkNoticeTarget(std::string noticeTarget){
    std::vector <string> targetVec;
    targetVec = stringToVec(privmsgTarget, ',');
    for (string elem : targetVec){
        if (!isValidChanName(elem) && !isValidNick(elem)){
            return (ERR_WRONGINPUT);
        }
        else{
            this->_targetVec.push_back(elem);
        }
    }
    return (0);
}

int ParcerResultNotice::checkNoticeParams(std::vector <std::string> messageVector){
    if (messageVector.size() == 1 ){
        return (ERR_NORECIPIENT);
    }
    if (messageVector.size() == 2 ){
        return (ERR_NOTEXTTOSEND);
    }
    if (messageVector[2][0] != ':'){
        this->_noticeMessage = messageVector[2]; 
    }
    else{
        for (int i = 2; i < messageVector.size(); ++i){
            this->_noticeMessage += messageVector[i];
        }
        this->_noticeMessage.erase(0, 1); // It removes the 1st char
                                            // (which in this case is ':')
    }
    int res = checkNoticeTarget(messageVector[1]);
    if (res > 0){
        return res;
    }
    return (res);
}
/*==========================================================*/
