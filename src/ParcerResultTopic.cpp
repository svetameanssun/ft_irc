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
/*----------------------------------------------------------*/
/*                   IS_VALID_CHANNEL_NAME                  */
/*----------------------------------------------------------*/
bool ParcerResultKick::isValidChanNameChar(int c) {
    if(c == '\0')
        return (false);
    else if(c == '\a')
        return (false);
    else if(c == '\r')
        return (false);
    else if(c == '\n')
        return (false);
    else if(c == ' ')
        return (false);
    else if(c == ',')
        return (false);
    else if(c == ':')
        return (false);
    else {
        return (true);
    }
}

bool ParcerResultKick::isValidChanName(std::string channelName) {
    size_t i = 0;
    if(channelName.empty()) {
        // NOT FORGET EVERYWHERE!
        return (false);
    }
    if((channelName.at(0) != '#') && (channelName.at(0) != '&')) {
        std::cout << "THIS\n";
        return (false);
    }
    if((channelName.length() > 200) || (channelName.length() == 1)) {
        return (false);
    }
    i++;
    for(; i < channelName.length(); ++i) {
        if(!isValidChanNameChar(channelName.at(i))) {
            return (false);
        }
    }
    return (true);
}

/*==========================================================*/

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
