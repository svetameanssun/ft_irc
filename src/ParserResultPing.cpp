#include "ParserResultPing.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultPing::ParserResultPing()
    : AParserResult(){
        _command = "PING";
}

ParserResultPing::ParserResultPing(const ParserResultPing &other): AParserResult(){
    this->_command = other._command;
    this->_pingParamsVec = other._pingParamsVec;
}

ParserResultPing& ParserResultPing::operator=(const ParserResultPing& other){
    if(this != &other) {
        this->_pingParamsVec = other._pinggParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParserResultPing::~ParserResultPing(){}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultPing::setParams(std::vector<std::string> pingCommand) {
  if (!pingCommand.empty() && pingCommand.size() > 1) {
    pingCommand.erase(pingCommand.begin());  // drop the first element, which is the command
  }
  this->_pingParamsVec = pingCommand;
}

const std::vector<std::string> ParserResultPing::getPingParams(void) const {
  return (this->_pingParamsVec);
}
const std::string ParserResultPing::getPingMessage(void) const {
  return (this->_pingMessage);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                        SPLIT                             */
/*----------------------------------------------------------*/
const std::vector<std::string> ParserResultPing::stringToVec(std::string str, char delim) {
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

int ParserResultPing::checkPingParams(std::vector <std::string> messageVector){
  // 0      1
  // PING :123
    if (messageVector.size() == 1 ){
        return (ERR_NORECIPIENT);
    }
    if (messageVector.size() == 2 ){
        return (ERR_NOTEXTTOSEND);
    }
    if (messageVector[2][0] != ':'){
        this->_pingMessage = messageVector[2]; 
    }
    else{
        for (size_t i = 2; i < messageVector.size(); ++i){
            this->_pingMessage += messageVector[i];
            this->_pingMessage += " ";

        }
      if (this->_pingMessage[0] == ':'){
        this->_pingMessage.erase(0, 1); // It removes the 1st char
      }                                      // (which in this case is ':')
        
      if (this->_pingMessage[_pingMessage.length()-1] == ' '){
        this->_pingMessage.erase(_pingMessage.length()-1, 1);
      }
    }
    return (0);
}
/*==========================================================*/


void ParserResultPing::printResult()const {
  std::cout << "Ping message: " << this->pingMessage;
  std::cout << std::endl;

}
