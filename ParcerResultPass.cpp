#include "ParcerResultPass.hpp"

ParcerResultPass::ParcerResultPass() : AParcerResult("PASS") {}
ParcerResultPass::~ParcerResultPass() {
	
};

ParcerResultPass::ParcerResultPass(const ParcerResultPass& other) {
  this->_passParams = other._passParams;
  this->_command = "PASS";
};

ParcerResultPass& ParcerResultPass::operator=(const ParcerResultPass& other) {
  if (this != &other) {
    this->_passParams = other._passParams;
    this->_command = "PASS";
  }
  return (*this);
}

void ParcerResultPass::setPassParams(std::vector<std::string> passCommand) {
  if (!passCommand.empty()) {
    passCommand.erase(passCommand.begin());  // drop the first element
  }
  this->_passParams = passCommand;
}

const std::vector<std::string> ParcerResultPass::getPassParams(void) const {
  return (this->_passParams);
}
