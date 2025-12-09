#include "ParserResultPass.hpp"

/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultPass::ParserResultPass() : AParserResult() {
  _command = "PASS";
}

ParserResultPass::ParserResultPass(const ParserResultPass& other):AParserResult(){
  this->_command = other._command;
  this->_passParamsVec = other._passParamsVec;
}

ParserResultPass& ParserResultPass::operator=(const ParserResultPass& other) {
  if (this != &other) {
    this->_passParamsVec = other._passParamsVec;
    this->_command = other._command;
  }
  return (*this);
}

ParserResultPass::~ParserResultPass() {}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultPass::setParams(std::vector<std::string> passCommand) {
  if (!passCommand.empty()) {
    passCommand.erase(passCommand.begin());  // drop the first element, which is the command
  }
  this->_passParamsVec = passCommand;
}

const std::vector<std::string> ParserResultPass::getPassParams(void) const {
  return (this->_passParamsVec);
}

/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultPass::printResult() const{

    std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator itVec = this->_passParamsVec.begin();
         itVec != this->_passParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }
}
/*==========================================================*/