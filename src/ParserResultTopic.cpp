#include "ParserResultTopic.hpp"
/*----------------------------------------------------------*/
/*                      CANONICAL PART                      */
/*----------------------------------------------------------*/
ParserResultTopic::ParserResultTopic()
    : AParserResult(), _topicQuery(false){
        _command = "TOPIC";
}

ParserResultTopic::ParserResultTopic(const ParserResultTopic &other) : AParserResult(){
    this->_command = other._command;
    this->_topicParamsVec = other._topicParamsVec;
}

ParserResultTopic& ParserResultTopic::operator=(const ParserResultTopic& other){
    if(this != &other) {
        this->_topicParamsVec = other._topicParamsVec;
        this->_command = other._command;
    }
    return (*this);
}

ParserResultTopic::~ParserResultTopic(){}

/*==========================================================*/

/*----------------------------------------------------------*/
/*                    SETTERS / GETTERS                     */
/*----------------------------------------------------------*/

void ParserResultTopic::setParams(std::vector<std::string> topicCommand) {
  if (!topicCommand.empty() && topicCommand.size() > 1) {
    topicCommand.erase(topicCommand.begin());  // drop the first element, which is the command
  }
  this->_topicParamsVec = topicCommand;
}

void ParserResultTopic::setTopic(std::string topic){
    this->_topicMessage = topic;
}

void ParserResultTopic::setTopicQuery(bool flag) {
    this->_topicQuery = flag;
}

const std::vector<std::string> ParserResultTopic::getTopicParams(void) const {
  return (this->_topicParamsVec);
}

const std::string ParserResultTopic::getTopicMessage(void) const{
    return (this->_topicMessage);
}

bool ParserResultTopic::isTopicQuery(void) {
    return (this->_topicQuery);
}


/*==========================================================*/
/*----------------------------------------------------------*/
/*                       IS_VALID...                        */
/*----------------------------------------------------------*/
int ParserResultTopic::checkTopicParams(std::vector <std::string> messageVector){
    
    //Command: TOPIC <channel> [ <topic> ]
    if (messageVector.size() == 1){
        return (ERR_NEEDMOREPARAMS);
    }
    if (!isValidChanName(messageVector.at(1))){
        return (ERR_NOSUCHCHANNEL);
    }
    if (messageVector.size() == 2){
        //[RUBEN] do we send this to the clien?
        //std::cout << this->getTopicMessage(); //WE have to send the message to the client from here!!! REMOVE
        this->setTopicQuery(1); // TOPIC #chanName
        return (0);
    }
    if (messageVector[2].empty()){
        this->setTopicQuery(1);// TOPIC
    }
    else{
        if (messageVector[2] == ":"){
            this->setTopic("");  // TOPIC #chan :   command to clear the topic
            this->setTopicQuery(0);
            return (0);
        }
    //TODO: check how to parse the "TOPIC #channel topic message"
        if (messageVector[2][0] != ':'){
            this->_topicMessage+= messageVector[2];
            return 0;
            //return (ERR_UNKNOWNCOMMAND);
        }
        for (size_t i = 2; i < messageVector.size(); i++){
            this->_topicMessage+= messageVector[i];
            this->_topicMessage+= " ";
        }
        this->_topicMessage.erase(_topicMessage.size()-1,1);
    }
    return (0);
}

/*==========================================================*/
/*----------------------------------------------------------*/
/*                      PRINT_RESULT                        */
/*----------------------------------------------------------*/

void ParserResultTopic::printResult() const{

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
