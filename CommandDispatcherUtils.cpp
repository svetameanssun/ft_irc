#include "CommandDispatcher.hpp"


int CommandDispatcher::dispatchPass(std::vector <std::string> messageVec){
    parcRes = ParcerResult()
    std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() == 1)
        return(ERR_NEEDMOREPARAMS);
    if (messageVec.size() > 2)
        return(ERR_NEEDLESSPARAMS);
    /*if (!flags.isRegistered())
        return(ERR_ALREADYREGISTRED);*/
    //return (handle("PASS", "password")); --> ERR_PASSWDMISMATCH
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchNick(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() == 1)
        return(ERR_NONICKNAMEGIVEN);
    if (!isValidNick(messageVec.at(1)))
        return(ERR_ERRONEUSNICKNAME);
    //handle("NICK", "nickname")--> ERR_NICKNAMEINUSE,
    //                          --> ERR_UNAVAILRESOURCE Returned by a server to a user trying to change nickname
    //                                   maybe?         when the desired nickname is blocked by the nick delay
    //                                                  mechanism.
    //                          --> change or assign nickname
    //NO nickcollision possible, no user mode restricted possible
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchJoin(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() > 3)
        return (ERR_NEEDLESSPARAMS);
    if (!isValidJoin){

    }
    return (RPL_WELCOME);
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
