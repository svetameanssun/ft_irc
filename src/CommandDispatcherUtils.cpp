#include "CommandDispatcher.hpp"

int CommandDispatcher::dispatchPass(std::vector<std::string> &messageVec) {
    ParserResultPass *resultPass = new ParserResultPass();
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
    // Transfer ownership into _parserResult
    this->_parserResult = resultPass;
    this->_parserResult->printResult();
    //the command PASS sould send the reply welcome,
    // along with 002, and 003, but I the replying to the client is not treated here, so
    // on success returna 0;
    // on failure returns ERR_;
    return(0);
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
    ParserResultNick *resultNick = new ParserResultNick();
    if (messageVec.size() == 1){
        delete(resultNick);
        return ERR_NONICKNAMEGIVEN;
    }
    if (messageVec.size() > 2){
        delete(resultNick);
        return ERR_NEEDLESSPARAMS;
    }
    if (!resultNick->isValidNick(messageVec.at(1))){
        delete(resultNick);
        return ERR_ERRONEUSNICKNAME;
    }
    resultNick->setParams(messageVec);
    // Transfer ownership into _parserResult
    this->_parserResult = resultNick;
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchUser(std::vector <std::string> &messageVec){
    //trailing params
    //USER <username> <realname>
    ParserResultUser * resultUser = new ParserResultUser();
    //std::cout << "HERE\n";
    int err = resultUser->checkUserParams(messageVec); 
    if(err > 0)
    {
        delete(resultUser);
        return (err);
    }
    resultUser->setParams(messageVec);
    // Transfer ownership to _parserResult 
    this->_parserResult = resultUser;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}

int CommandDispatcher::dispatchJoin(std::vector<std::string> &messageVec) {
    ParserResultJoin *resultJoin = new ParserResultJoin();
    int res = resultJoin->checkJoinParams(messageVec);
    if (res > 0){
        delete(resultJoin);
        return res;
    }
    resultJoin->setParams(messageVec);
    // Transfer ownership to _parcerResult
    this->_parserResult = resultJoin;
    this->_parserResult->printResult();
    return(0);
}

int CommandDispatcher::dispatchPart(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultPart * resultPart = new ParserResultPart();
    int res = resultPart->checkPartParams(messageVec);
    //if checkPartParams returns anything other than 0 - the command input is wrong
    if (res > 0)
    {
        delete resultPart;
        return (res);
    }
    resultPart->setParams(messageVec);
    this->_parserResult = resultPart;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}


int CommandDispatcher::dispatchMode(std::vector <std::string> &messageVec){
    ParserResultMode * resultMode = new ParserResultMode();
    if (messageVec.size() < 3){
        delete(resultMode);
        return ERR_NEEDMOREPARAMS;
    }
    if (messageVec.size() > 4){
        delete(resultMode);
        return ERR_NEEDLESSPARAMS;
    }
    resultMode->setParams(messageVec);
    if(int err = 0)//resultMode->checkModeParams(messageVec))
    {
        delete(resultMode);
        return (err);
    }
    this->_parserResult = resultMode;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultTopic * resultTopic = new ParserResultTopic();
    int res = resultTopic->checkTopicParams(messageVec);
    if (res > 0){
        delete(resultTopic);
        return  ERR_UNKNOWNCOMMAND;
    }
    resultTopic->setParams(messageVec);
    this->_parserResult = resultTopic;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return (res); // it will return 0 when the server will send the topic to the client.
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> &messageVec){
    ParserResultInvite * resultInvite = new ParserResultInvite();
    int res = resultInvite->checkInviteParams(messageVec);
    if (res > 0)
    {
        delete resultInvite;
        return ERR_UNKNOWNCOMMAND;
    }
    resultInvite->setParams(messageVec);
    this->_parserResult = resultInvite;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0); // in the end, server sends RPL_INVITING to the user
}

int CommandDispatcher::dispatchKick(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultKick * resultKick = new ParserResultKick();
    int res = resultKick->checkKickParams(messageVec);
    //if checkKickParams returns anything other than 0 - the command input is wrong
    if (res > 0)
    {
        delete resultKick;
        return (res);
    }
    resultKick->setParams(messageVec);
    this->_parserResult = resultKick;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    //return (RPL_WELCOME);
    return(0);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultPrivmsg * resultPrivmsg = new ParserResultPrivmsg();
    int res = resultPrivmsg->checkPrivmsgParams(messageVec);
    if (res > 0)
    {
        delete resultPrivmsg;
        return (res);
    }
    resultPrivmsg->setParams(messageVec);
    this->_parserResult = resultPrivmsg;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}

int CommandDispatcher::dispatchNotice(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultNotice * resultNotice = new ParserResultNotice();
    if (!resultNotice->checkNoticeParams(messageVec))
    {
        delete resultNotice;
        return ERR_UNKNOWNCOMMAND;
    }
    resultNotice->setParams(messageVec);
    this->_parserResult = resultNotice;
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}

int CommandDispatcher::dispatchQuit(std::vector <std::string> &messageVec){
    //trailing params
    ParserResultQuit * resultQuit = new ParserResultQuit();
    resultQuit->collectQuitMessage(messageVec);
    resultQuit->setParams(messageVec);
    this->_parserResult->printResult();
    std::cout << messageVec.at(0)<< std::endl;
    return(0);
}
