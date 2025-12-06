#include "ParcerResultPass.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultPass::ParcerResultPass() : AParcerResult() {
  _command = "PASS";
}

ParcerResultPass::ParcerResultPass(const ParcerResultPass& other):AParcerResult(){
  this->_command = other._command;
  this->_passParamsVec = other._passParamsVec;
}

ParcerResultPass& ParcerResultPass::operator=(const ParcerResultPass& other) {
  if (this != &other) {
    this->_passParamsVec = other._passParamsVec;
    this->_command = other._command;
  }
  return (*this);
}

ParcerResultPass::~ParcerResultPass() {}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultPass::setParams(std::vector<std::string> passCommand) {
  if (!passCommand.empty()) {
    passCommand.erase(passCommand.begin());  // drop the first element, which is the command
  }
  this->_passParamsVec = passCommand;
}

const std::vector<std::string> ParcerResultPass::getPassParams(void) const {
  return (this->_passParamsVec);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultPass::printResult() const{

    std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator itVec = this->_passParamsVec.begin();
         itVec != this->_passParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }
}
/*==========================================================*/
