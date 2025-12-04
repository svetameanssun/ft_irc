#include "ParcerResultQuit.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/

ParcerResultQuit::ParcerResultQuit()
    : AParcerResult() {
    _command = "QUIT";
}

ParcerResultQuit::ParcerResultQuit(const ParcerResultQuit& other): AParcerResult() {
    this->_command = other._command;
    this->_quitParamsVec = other._quitParamsVec;
}


ParcerResultQuit& ParcerResultQuit::operator=(const ParcerResultQuit& other) {
    if(this != &other) {
        this->_quitParamsVec = other._quitParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultPart::~ParcerResultPart() {}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultQuit::setParams(std::vector<std::string> quitCommand) {
    this->_quitParamsVec = quitCommand;
}

const std::vector<std::string> ParcerResultQuit::getQuitParams(void) const{
	return (this->_quitParamsVec);
}

const std::vector<std::string> getQuitMessage(void) const{
	return(this->_quitMessage);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                    COLLECT_QUIT_MESSAGE                  */
/*----------------------------------------------------------*/
//It is important to use a reference here, 
// because I will cut-off the trailing ending
void  ParcerResultQuit::collectQuitMessage (std::vector<std::string> &messageVector){
  
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

void ParcerResultPart::printResult()const {
    std::cout << "Quit Message:\n"
    std::cout << this->_quitMessage << std::endl;   
}
/*==========================================================*/
