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
int ParcerResultTopic::checkTopicParams(std::vector <std::string> messageVector){
    if (messageVector.size() == 1){
        return (ERR_NEEDMOREPARAMS);
    }
    if (!isValidChanName(messageVector.at(1))){
        return (ERR_NOSUCHCHAN);
    }
    if (messageVector.size() == 2){
        std::cout << this->_topicMessage(); //I have to send the message to the client from here!!!
        return (0);
    }
    if (messageVector[2][0] != ':'){
        return (ERR_UNKNOWNCOMMAND);
    }
    for (int i = 2; i < messageVector.size(); i++){
        this->_topicMessage+= messageVector[i];
    }
    return (0);
}

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

/*
3.2.4 Topic message
 Command: TOPIC
 Parameters: <channel> [ <topic> ]
 The TOPIC command is used to change or view the topic of a channel.
 The topic for channel <channel> is returned if there is no <topic>
 given. If the <topic> parameter is present, the topic for that
 channel will be changed, if this action is allowed for the user
 requesting it. If the <topic> parameter is an empty string, the
 topic for that channel will be removed.
 Numeric Replies:
 
 ERR_NEEDMOREPARAMS
 ERR_NOTONCHANNEL
 RPL_NOTOPIC RPL_TOPIC
 ERR_CHANOPRIVSNEEDED
 ERR_NOCHANMODES
 
 Examples:
     :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic 
                                                         User Wiz setting the topic.
     TOPIC #test :another topic
                                                         Command to set the topic on #test
                                                         to "another topic".
                                                         
     TOPIC #test :                                       Command to clear the topic on #test.
     
     TOPIC #test                                         Command to check the topic for
*/
