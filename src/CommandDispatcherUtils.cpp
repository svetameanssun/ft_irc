#include "CommandDispatcher.hpp"

void printMap(const std::map<std::string, std::string> &myMap) {
    if (myMap.empty())
        return;

    std::cout << "[KEY] = VALUE\n";
    for (std::map<std::string, std::string>::const_iterator it = myMap.begin();
         it != myMap.end(); ++it) {
        std::cout << "[" << it->first << "] = " << it->second << "\n";
    }
}

void printVec(const std::vector<std::string> &myVec) {
    if (myVec.empty())
        return;

    std::cout << "VECTOR:\n";
    for (std::vector<std::string>::const_iterator it = myVec.begin();
         it != myVec.end(); ++it) {
        std::cout << *it << "\n";
    }
}


int CommandDispatcher::dispatchPass(std::vector<std::string> &messageVec) {


    ParcerResultPass *resultPass = new ParcerResultPass();

    if (messageVec.size() == 1)
        return ERR_NEEDMOREPARAMS;
    if (messageVec.size() > 2)
        return ERR_NEEDLESSPARAMS;

    resultPass->setPassParams(messageVec);

    // Transfer ownership into _parcerResult
    _parcerResult = resultPass;
    _parcerResult->printResult();
    printVec(resultPass->getPassParams());
    printVec(messageVec);

    return RPL_WELCOME;
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
        ParcerResultNick *resultNick = new ParcerResultNick();

    if (messageVec.size() == 1)
        return ERR_NONICKNAMEGIVEN;
    if (!resultNick->isValidNick(messageVec))
        return ERR_ERRONEUSNICKNAME;

    resultNick->setNickParams(messageVec);

    // Transfer ownership into _parcerResult
    _parcerResult = resultNick;
    _parcerResult->printResult();

    return RPL_WELCOME;
}


int CommandDispatcher::dispatchJoin(std::vector<std::string> &messageVec) {
    ParcerResultJoin *resultJoin = new ParcerResultJoin();
    if (messageVec.size() < 2)
        return ERR_NEEDMOREPARAMS;
    if (messageVec.size() > 3)
        return ERR_NEEDLESSPARAMS;
    if (!resultJoin->isValidJoin(messageVec)){
        return ERR_UNKNOWNCOMMAND;
    }

    resultJoin->setJoinParams(messageVec);

    // Transfer ownership to _parcerResult
    _parcerResult = resultJoin;

    //_parcerResult->printResult();
    printVec(resultJoin->getJoinParamsVec());
    //printVec(messageVec);


    return RPL_WELCOME;
}



int CommandDispatcher::dispatchUser(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}


int CommandDispatcher::dispatchQuit(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}



int CommandDispatcher::dispatchMode(std::vector <std::string> &messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0) << std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> &messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchKick(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> &messageVec){
    //trailing params
    
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInfo(std::vector <std::string> &messageVec){
    std::cout << messageVec.at(0)<< "\n" <<std::endl;
    return (RPL_WELCOME);
}
