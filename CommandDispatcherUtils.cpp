#include "CommandDispatcher.hpp"

int CommandDispatcher::dispatchPass(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchNick(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchUser(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}


int CommandDispatcher::dispatchQuit(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchJoin(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchMode(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchTopic(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0) << std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInvite(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchKick(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchPrivmsg(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchInfo(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< "\n" <<std::endl;
    return (RPL_WELCOME);
}
