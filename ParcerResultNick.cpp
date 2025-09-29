#include "ParcerResultNick.hpp"

ParcerResultNick::ParcerResultNick()
  : AParcerResult("NICK") {}
ParcerResultNick::~ParcerResultNick() {}
ParcerResultNick::ParcerResultNick(const ParcerResultNick& other)
  : AParcerResult("NICK") {
  this->_nickParams = other._nickParams;
  this->_command = "NICK";
};

ParcerResultNick& ParcerResultNick::operator=(const ParcerResultNick& other) {
  if (this != &other) {
    this->_nickParams = other._nickParams;
    this->_command = "NICK";
  }
  return (*this);
}


void ParcerResultNick::setNickParams(std::vector<std::string> nickCommand) {
   if (!nickCommand.empty()) {
    nickCommand.erase(nickCommand.begin());  // drop the first element, wich is the NICK command
  }
  this->_nickParams = nickCommand;
}

const std::vector<std::string> ParcerResultNick::getNickParams(void)const {
    return (this->_nickParams);
}

bool ParcerResultNick::isSpecialChar(int c) {
  std::string specialChars = "[]\\`^{}";
  if (specialChars.find(c) == std::string::npos) return (0);
  return (1);
}

bool ParcerResultNick::isValidNick(std::vector<std::string> nickCommand) {
  std::string nickname = nickCommand.at(1);
  if (nickname.empty())
    return (0);
  if (nickname.at(0) == '-' || isdigit(nickname.at(0)))
    return (0);
  if (!isalpha(nickname.at(0)) && !isSpecialChar(nickname.at(0)))
    return (0);
  if (nickname.length() > 9) return (0);
    for (long unsigned int i = 1; i < nickname.length(); ++i) {
      if (!isdigit(nickname.at(i)) && !isalpha(nickname.at(i)) &&
        !isSpecialChar(nickname.at(i)) && nickname.at(i) != '-'){
        return (0);
      }
  }
  return (1);
}
