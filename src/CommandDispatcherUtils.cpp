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
    _parcerResult = resultPass;
    _parcerResult->printResult();

    return RPL_WELCOME;
}

int CommandDispatcher::dispatchNick(std::vector<std::string> &messageVec) {
        ParcerResultNick *resultNick = new ParcerResultNick();

    if (messageVec.size() == 1){
        delete(resultNick);
        return ERR_NONICKNAMEGIVEN;
    }
    if (!resultNick->isValidNick(messageVec)){
        delete(resultNick);
        return ERR_ERRONEUSNICKNAME;
    }

    resultNick->setParams(messageVec);

    // Transfer ownership into _parcerResult
    _parcerResult = resultNick;
    _parcerResult->printResult();

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
    _parcerResult = resultJoin;

    _parcerResult->printResult();
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
    _parcerResult = resultUser;

    _parcerResult->printResult();
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
