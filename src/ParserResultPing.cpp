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
        this->_pingParamsVec = other._pingParamsVec;
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
/*                       IS_VALID_PARAM                      */
/*----------------------------------------------------------*/

int ParserResultPing::checkPingParams(std::vector <std::string> messageVector){
  // 0      1
  // PING :123
  if (messageVector.size() == 1 ){
    return (ERR_NEEDMOREPARAMS);
  }
  if (!messageVector[1].empty() && messageVector[1][0] != ':'){
      this->_pingMessage = messageVector[1]; 
  }
  else{
    for (size_t i = 1; i < messageVector.size(); ++i){
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
  std::cout << "Ping message: " << this->_pingMessage;
  std::cout << std::endl;

}
