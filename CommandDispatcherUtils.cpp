#include "CommandDispatcher.hpp"


int CommandDispatcher::dispatchPass(std::vector<std::string> messageVec) {
    std::auto_ptr<ParcerResultPass> resultPass(new ParcerResultPass());

    if (messageVec.size() == 1)
        return ERR_NEEDMOREPARAMS;
    if (messageVec.size() > 2)
        return ERR_NEEDLESSPARAMS;

    resultPass->setPassParams(messageVec);

    // Transfer ownership into _parcerResult
    _parcerResult = resultPass;

    return RPL_WELCOME;
}

int CommandDispatcher::dispatchNick(std::vector<std::string> messageVec) {
    std::auto_ptr<ParcerResultNick> resultNick(new ParcerResultNick());

    if (messageVec.size() == 1)
        return ERR_NONICKNAMEGIVEN;
    if (!resultNick->isValidNick(messageVec))
        return ERR_ERRONEUSNICKNAME;

    resultNick->setNickParams(messageVec);

    // Transfer ownership into _parcerResult
    _parcerResult = resultNick;

    return RPL_WELCOME;
}


int CommandDispatcher::dispatchJoin(std::vector<std::string> messageVec) {
    std::auto_ptr<ParcerResultJoin> resultJoin(new ParcerResultJoin());

    if (messageVec.size() < 2)
        return ERR_NEEDMOREPARAMS;
    if (messageVec.size() > 3)
        return ERR_NEEDLESSPARAMS;
    if (!resultJoin->isValidJoin(messageVec))
        return ERR_UNKNOWNCOMMAND;

    resultJoin->setJoinParams(messageVec);

    // Transfer ownership to _parcerResult
    _parcerResult = resultJoin;

    _parcerResult->printVec();
    _parcerResult->printMap();

    return RPL_WELCOME;
}



int CommandDispatcher::dispatchUser(std::vector <std::string> messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}


int CommandDispatcher::dispatchQuit(std::vector <std::string> messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}



int CommandDispatcher::dispatchMode(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> messageVec){
    //trailing params
    
    std::cout << messageVec.at(0) << std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchKick(std::vector <std::string> messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInfo(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< "\n" <<std::endl;
    return (RPL_WELCOME);
}
