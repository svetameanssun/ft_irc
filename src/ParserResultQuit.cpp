#include "ParserResultQuit.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParserResultQuit::ParserResultQuit()
    : AParserResult() {
    _command = "QUIT";
}

ParserResultQuit::ParserResultQuit(const ParserResultQuit& other): AParserResult() {
    this->_command = other._command;
    this->_quitParamsVec = other._quitParamsVec;
}


ParserResultQuit& ParserResultQuit::operator=(const ParserResultQuit& other) {
    if(this != &other) {
        this->_quitParamsVec = other._quitParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParserResultPart::~ParserResultPart() {}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultQuit::setParams(std::vector<std::string> quitCommand) {
    this->_quitParamsVec = quitCommand;
}

const std::vector<std::string> ParserResultQuit::getQuitParams(void) const{
	return (this->_quitParamsVec);
}

const std::vector<std::string> ParserResultQuit::getQuitMessage(void) const{
	return(this->_quitMessage);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    COLLECT_QUIT_MESSAGE                  */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
void ParserResultQuit::collectQuitMessage (std::vector<std::string> &messageVector){
	if (messageVector.size() == 1){
    this->_quitMessage = "default";
  }
  if (messageVector.size() > 1){
    if (messageVector[1][0] == ':'){
      for (size_t i = 1; i < messageVector.size(); i++){
				this->_quitMessage += messageVector[i];
				this->_quitMessage += " ";
			}
    }
    else{
      this->_quitMessage = messageVector[1];
    }
  }
  
  if(_quitMessage.at(0) == ':'){
				_quitMessage.erase(0, 1);
	}
	//erase the last space, if there is one
  if (_quitMessage[_quitMessage.length() - 1] == ' '){
	  _quitMessage.erase(_quitMessage.length() - 1 , 1);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultQuit::printResult()const {
    std::cout << "Quit Message:\n"
    std::cout << this->_quitMessage << std::endl;   
}
/*==========================================================*/
