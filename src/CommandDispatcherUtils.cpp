#include "CommandDispatcher.hpp"

int CommandDispatcher::dispatchPass(std::vector<std::string> &messageVec) {


    ParcerResultPass *resultPass = new ParcerResultPass();
    //PASS <password>
    if (messageVec.size() <= 1 ){
        delete(resultPass);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 2){
        return ERR_NEEDLESSPARAMS;
        delete(resultPass);
    }
    resultPass->setParams(messageVec);

    // Transfer ownership into _parcerResult
    this->_parcerResult = resultPass;
    this->_parcerResult->printResult();
    //the command PASS sould send the reply welcome,
    // along with 002, and 003, but I the replying to the client is not treated here, so
    // on success returna 0;
    // on failure returns ERR_;
    //return RPL_WELCOME;
    return(0);
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
        ParcerResultNick *resultNick = new ParcerResultNick();

    if (messageVec.size() <= 1){
        delete(resultNick);
        return ERR_NONICKNAMEGIVEN;
    }
    if (messageVec.size() > 2){
        return ERR_NEEDLESSPARAMS;
        delete(resultNick);
    }
    if (!resultNick->isValidNick(messageVec)){
        delete(resultNick);
        return ERR_ERRONEUSNICKNAME;
    }
    resultNick->setParams(messageVec);
    // Transfer ownership into _parcerResult
    this->_parcerResult = resultNick;
    this->_parcerResult->printResult();
    //return RPL_WELCOME;
    return(0);
}


int CommandDispatcher::dispatchJoin(std::vector<std::string> &messageVec) {
    ParcerResultJoin *resultJoin = new ParcerResultJoin();
    if (messageVec.size() < 2){
        delete(resultJoin);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 3){
        delete(resultJoin);
        return ERR_NEEDLESSPARAMS;
    }
    if (!resultJoin->isValidJoin(messageVec)){
        delete(resultJoin);
        return ERR_UNKNOWNCOMMAND;
    }

    resultJoin->setParams(messageVec);

    // Transfer ownership to _parcerResult
    this->_parcerResult = resultJoin;
    this->_parcerResult->printResult();
    //return RPL_WELCOME;
    return(0);
}



int CommandDispatcher::dispatchUser(std::vector <std::string> &messageVec){
    //trailing params
    //USER <username> <realname>
    ParcerResultUser * resultUser = new ParcerResultUser();
    //std::cout << "HERE\n";
    int err = resultUser->checkUserParams(messageVec); 
    if(err > 0)
    {
        delete(resultUser);
        return (err);
    }
    resultUser->setParams(messageVec);
    // Transfer ownership to _parcerResult 
    this->_parcerResult = resultUser;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchMode(std::vector <std::string> &messageVec){
    ParcerResultMode * resultMode = new ParcerResultMode();
    if (messageVec.size() < 3){
        delete(resultMode);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 4){
        delete(resultMode);
        return ERR_NEEDLESSPARAMS;
    }
    resultMode->setParams(messageVec);
    if(int err = resultMode->checkModeParams(messageVec))
    {
        delete(resultMode);
        return (err);
    }
    this->_parcerResult = resultMode;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> &messageVec){
    //trailing params
    ParcerResultTopic * resultTopic = new ParcerResultTopic();
    int res = resultTopic->checkTopicParams(messageVec);
    if (res > 0){
        delete(resultTopic);
        return  ERR_UNKNOWNCOMMAND;
    }
    resultTopic->setParams(messageVec);
    this->_parcerResult = resultTopic;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> &messageVec){
    ParcerResultInvite * resultInvite = new ParcerResultInvite();
    if (!resultInvite->checkInviteParams(messageVec))
    {
        delete resultInvite;
        return ERR_UNKNOWNCOMMAND;
    }
    resultInvite->setParams(messageVec);
    this->_parcerResult = resultInvite;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchKick(std::vector <std::string> &messageVec){
    //trailing params
    
    ParcerResultKick * resultKick = new ParcerResultKick();
    int res = resultKick->checkKickParams(messageVec);
    //if checkKickParams returns anything other than 0 - the command input is wrong
    if (res > 0)
    {
        delete resultKick;
        return (res);
    }
    resultKick->setParams(messageVec);
    this->_parcerResult = resultKick;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> &messageVec){
    //trailing params
    
    ParcerResultPrivmsg * resultPrivmsg = new ParcerResultPrivmsg();
    if (!resultPrivmsg->checkPrivmsgParams(messageVec))
    {
        delete resultPrivmsg;
        return ERR_UNKNOWNCOMMAND;
    }
    resultPrivmsg->setParams(messageVec);
    this->_parcerResult = resultPrivmsg;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchQuit(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}
