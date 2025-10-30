#include "ParcerResultTopic.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParcerResultTopic::ParcerResultTopic()
    : AParcerResult(){
        _command = "Topic";
}

ParcerResultTopic::ParcerResultTopic(const ParcerResultTopic &other){
    this->_command = other._command;
    this->_topicParamsVec = other._topicParamsVec;
}

ParcerResultTopic& ParcerResultTopic::operator=(const ParcerResultTopic& other){
    if(this != &other) {
        this->_topicParamsVec = other._topicParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParcerResultTopic::~ParcerResultTopic(){}

/*==========================================================*/


/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParcerResultTopic::setParams(std::vector<std::string> topicCommand) {
  if (!topicCommand.empty()) {
    topicCommand.erase(topicCommand.begin());  // drop the first element, which is the command
  }
  this->_topicParamsVec = topicCommand;
}

const std::vector<std::string> ParcerResultTopic::getTopicParams(void) const {
  return (this->_topicParamsVec);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                       IS_VALID...                        */
/*----------------------------------------------------------*/


/*==========================================================*/
/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParcerResultTopic::printResult() const{

    std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator itVec = this->_topicParamsVec.begin();
         itVec != this->_topicParamsVec.end(); ++itVec) {
        std::cout << *itVec << "\n";
    }

}
/*==========================================================*/