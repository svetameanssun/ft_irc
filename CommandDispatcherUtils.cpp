#include "CommandDispatcher.hpp"


int CommandDispatcher::dispatchPass(std::vector <std::string> messageVec){
    /*class CBase {};
class CDerived: public CBase {};
CBase * a = new CBase;
CDerived * b = static_cast<CDerived*>(a);
 */
    ParcerResultPass resultPass;

    //std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() == 1){
        return(ERR_NEEDMOREPARAMS);
    }
    if (messageVec.size() > 2){
        return(ERR_NEEDLESSPARAMS);
    }
    resultPass.setPassParams(messageVec);
    _parcerResult = &resultPass;
    //later i can get the info castiing _parcerRes with static_cast
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchNick(std::vector <std::string> messageVec){
    ParcerResultNick resultNick;
    //std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() == 1)
        return(ERR_NONICKNAMEGIVEN);
    if (!resultNick.isValidNick(messageVec))
        return(ERR_ERRONEUSNICKNAME);
    resultNick.setNickParams(messageVec);
    _parcerResult = &resultNick;
    return (RPL_WELCOME);
}

int CommandDispatcher::dispatchJoin(std::vector <std::string> messageVec){
    //std::cout << messageVec.at(0)<< std::endl;
    ParcerResultJoin resultJoin;
    if (messageVec.size() < 2)
        return (ERR_NEEDMOREPARAMS);
    if (messageVec.size() > 3)
        return (ERR_NEEDLESSPARAMS);
    if (!resultJoin.isValidJoin(messageVec)){
        return (ERR_UNKNOWNCOMMAND);
    }
    resultJoin.setJoinParams(messageVec);
    _parcerResult = &resultJoin;
    printVec(resultJoin.getJoinParamsVec());
    printMap(resultJoin.getJoinParamsMap());
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
