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

    return RPL_WELCOME;
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
        ParcerResultNick *resultNick = new ParcerResultNick();

    if (messageVec.size() <= 1){
        delete(resultNick);
        return ERR_NONICKNAMEGIVEN;
    }
    if (messageVec.size() > 2){
        return ERR_NEEDLESSPARAMS;
        delete(resultPass);
    }
    if (!resultNick->isValidNick(messageVec)){
        delete(resultNick);
        return ERR_ERRONEUSNICKNAME;
    }
    resultNick->setParams(messageVec);
    // Transfer ownership into _parcerResult
    this->_parcerResult = resultNick;
    this->_parcerResult->printResult();
    return RPL_WELCOME;
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
    return RPL_WELCOME;
}



int CommandDispatcher::dispatchUser(std::vector <std::string> &messageVec){
    //trailing params
    //USER <username> <realname>
    ParcerResultUser * resultUser = new ParcerResultUser();
    //std::cout << "HERE\n";
    if(int err = resultUser->checkUserParams(messageVec))
    {
        delete(resultUser);
        return (err);
    }
    resultUser->setParams(messageVec);
    // Transfer ownership to _parcerResult 
    this->_parcerResult = resultUser;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchMode(std::vector <std::string> &messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    ParcerResultMode * resultMode = new ParcerResultMode();
    if (messageVec.size() < 3){
        delete(resultMode);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 4){
        delete(resultMode);
        return ERR_NEEDLESSPARAMS;
    }
    if(int err = resultMode->checkModeParams(messageVec))
    {
        delete(resultMode);
        return (err);
    }
    resultMode->setParams(messageVec);
    this->_parcerResult = resultMode;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;

    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> &messageVec){
    //trailing params
    ParcerResultTopic * resultTopic = new ParcerResultTopic();
    //check the command vector
    resultTopic->setParams(messageVec);
    this->_parcerResult = resultTopic;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> &messageVec){
    ParcerResultInvite * resultInvite = new ParcerResultInvite();
    //check the command vector
    resultInvite->setParams(messageVec);
    this->_parcerResult = resultInvite;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchKick(std::vector <std::string> &messageVec){
    //trailing params
    
    ParcerResultKick * resultKick = new ParcerResultKick();
    //check the command vector
    resultKick->setParams(messageVec);
    this->_parcerResult = resultKick;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> &messageVec){
    //trailing params
    
    ParcerResultPrivmsg * resultPrivmsg = new ParcerResultPrivmsg();
    //check the command vector
    resultPrivmsg->setParams(messageVec);
    this->_parcerResult = resultPrivmsg;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInfo(std::vector <std::string> &messageVec){
    ParcerResultInfo * resultInfo = new ParcerResultInfo();
    //check the command vector
    resultInfo->setParams(messageVec);
    this->_parcerResult = resultInfo;
    this->_parcerResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchQuit(std::vector <std::string> &messageVec){
    //trailing params

    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}