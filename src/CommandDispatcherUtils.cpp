#include "CommandDispatcher.hpp"

int CommandDispatcher::dispatchPass(std::vector<std::string> &messageVec) {
    //PASS <password>
    if (messageVec.size() <= 1 ){
        //delete(_parserResult);
        return ERR_NEEDMOREPARAMS;
    }
    /*if (messageVec.size() > 2){
        //delete(_parserResult);
        return ERR_NEEDLESSPARAMS;
    }*/
    _parserResult->setParams(messageVec);
    // Transfer ownership into _parserResult
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
    if (messageVec.size() == 1){
        //delete(_parserResult);
        return (ERR_NONICKNAMEGIVEN);
    }
    /*if (messageVec.size() > 2){
        //delete(_parserResult);
        return ERR_NEEDLESSPARAMS;
    }*/
    if (!_parserResult->isValidNick(messageVec.at(1))){
        //delete(_parserResult);
        return ERR_ERRONEUSNICKNAME;
    }
    _parserResult->setParams(messageVec);
    // Transfer ownership into _parserResult
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchUser(std::vector <std::string> &messageVec){
    //trailing params
    //USER <username> <realname>
    std::cout << _parserResult << std::endl;
    int err = _parserResult->checkUserParams(messageVec);
    if(err > 0)
    {
        //delete(_parserResult);

        return (err);
    }
    _parserResult->setParams(messageVec);
    // Transfer ownership to _parserResult 
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchJoin(std::vector<std::string> &messageVec) {
    int res = _parserResult->checkJoinParams(messageVec);
    if (res > 0){
        //delete(_parserResult);
        return res;
    }
    _parserResult->setParams(messageVec);
    // Transfer ownership to _parserResult
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchPart(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkPartParams(messageVec);
    //if checkPartParams returns anything other than 0 - the command input is wrong
    if (res > 0)
    {
        //delete(_parserResult);
        return (res);
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0);
}


int CommandDispatcher::dispatchMode(std::vector <std::string> &messageVec){
    if (messageVec.size() < 3){
        //delete(_parserResult);

        return ERR_NEEDMOREPARAMS;
    }
    /*if (messageVec.size() > 4){
        //delete(_parserResult);

        return ERR_NEEDLESSPARAMS;
    }*/
    _parserResult->setParams(messageVec);
    int err = 0; //resultMode->checkModeParams(messageVec))
    if(err == 0)//resultMode->checkModeParams(messageVec))
    {
        //delete(_parserResult);
        return (err);
    }
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkTopicParams(messageVec);
    if (res > 0){
        //delete(_parserResult);
        return (res);
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return (res);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> &messageVec){
    int res = _parserResult->checkInviteParams(messageVec);
    if (res > 0)
    {
        //delete(_parserResult);
        return ERR_UNKNOWNCOMMAND;
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0); // in the end, server sends RPL_INVITING to the user
}

int CommandDispatcher::dispatchKick(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkKickParams(messageVec);
    //if checkKickParams returns anything other than 0 - the command input is wrong
    if (res > 0)
    {
        //delete(_parserResult);
        return (res);
    }
    _parserResult->setParams(messageVec);

    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkPrivmsgParams(messageVec);
    if (res > 0)
    {
        //delete(_parserResult);
        return (res);
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchNotice(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkNoticeParams(messageVec);
    if (res > 0)
    {
        //delete(_parserResult);
        return ERR_UNKNOWNCOMMAND;
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchQuit(std::vector <std::string> &messageVec){
    //trailing params
    _parserResult->collectQuitMessage(messageVec);
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchPing(std::vector <std::string> &messageVec){
    //trailing params
    int res = _parserResult->checkPingParams(messageVec);
    if (res > 0)
    {
        //delete(_parserResult);
        return (res);
    }
    _parserResult->setParams(messageVec);
    this->_parserResult->printResult();
    return(0);
}


