#include "ParserResultNotice.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultNotice::ParserResultNotice()
    : AParserResult(){
        _command = "NOTICE";
}

ParserResultNotice::ParserResultNotice(const ParserResultNotice &other): AParserResult(){
    this->_command = other._command;
    this->_noticeParamsVec = other._noticeParamsVec;
    this->_targetVec = other._targetVec;
}

ParserResultNotice& ParserResultNotice::operator=(const ParserResultNotice& other){
    if(this != &other) {
        this->_noticeParamsVec = other._noticeParamsVec;
        this->_targetVec = other._targetVec;
        this->_command = other._command;
    }
    return (*this);
}

ParserResultNotice::~ParserResultNotice(){}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultNotice::setParams(std::vector<std::string> noticeCommand) {
  if (!noticeCommand.empty() && noticeCommand.size() > 1) {
    noticeCommand.erase(noticeCommand.begin());  // drop the first element, which is the command
  }
  this->_noticeParamsVec = noticeCommand;
}

const std::vector<std::string> ParserResultNotice::getNoticeParams(void) const {
  return (this->_noticeParamsVec);
}

const std::vector<std::string> ParserResultNotice::getTargetVec(void) const {
  return (this->_targetVec);
}

const std::string ParserResultNotice::getNoticeMessage(void) const {
  return (this->_noticeMessage);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                        SPLIT                             */
/*----------------------------------------------------------*/
const std::vector<std::string> ParserResultNotice::stringToVec(std::string str, char delim) {
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
int ParserResultNotice::checkNoticeTarget(std::string noticeTarget){
    std::vector <std::string> targetVec;
    targetVec = stringToVec(noticeTarget, ',');
    for (size_t i = 0; i < targetVec.size(); i++){
        if (!isValidChanName(targetVec[i]) && !isValidNick(targetVec[i])){
            return (ERR_WRONGINPUT);
        }
        else{
            this->_targetVec.push_back(targetVec[i]);
        }
    }
    return (0);
}

int ParserResultNotice::checkNoticeParams(std::vector <std::string> messageVector){
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
        for (size_t i = 2; i < messageVector.size(); ++i){
            this->_noticeMessage += messageVector[i];
            this->_noticeMessage += " ";

        }
        this->_noticeMessage.erase(0, 1); // It removes the 1st char
                                            // (which in this case is ':')
        this->_noticeMessage.erase(_noticeMessage.size()-1, 1);                              
        
    }
    int res = checkNoticeTarget(messageVector[1]);
    if (res > 0){
        return res;
    }
    return (res);
}

/*==========================================================*/

void ParserResultNotice::printResult()const {
   
  std::cout << std::endl;

}