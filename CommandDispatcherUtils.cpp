#include "CommandDispatcher.hpp"

bool isSpecialChar(int c){
    
    std::string specialChars = "[]\\`^{}";
    if (specialChars.find(c) ==  std::string::npos)
        return (0);
    return (1);
}

bool CommandDispatcher::isValidNick(std::string nick){
    if (nick.empty())
        return (0);
    if (nick.at(0) == '-' || isdigit(nick.at(0)))
        return (0);
    if (!isalpha(nick.at(0)) && !isSpecialChar(nick.at(0)))
        return (0);
    if (nick.length() > 9)
        return (0);
    for (int i = 1; i < nick.length(); ++i){
        if (nick.at(i) > 127) // non-ASCII
            return 0;
        if (!isdigit(nick.at(i)) && !isalpha(nick.at(i)) && !isSpecialChar(nick.at(i)) && nick.at(i) != '-')
            return (0);
    }
    return (1);
}

bool CommandDispatcher::isValidJoin(std::vector <std::string> messageVector){
   
    // 
    if (messageVector.size() == 2){
        parcRes.set
        //check, how many channels i want to join
        //  make a vector out of channels
        // and then handle("JOIN", channelVec)
         //!= '#' && first != '&' && first != '+' && first != '!'
         //&foo,+bar,#foof
    }

    if (messageVector.size() == 3){
        //check how many channels I want to join//
        // make a map [key] - channels name/
        //            value - password.
        // and then handle("JOIN", channelMap)
        //&foo,+bar,#foof
        //fubar,foobar
    }
}


int CommandDispatcher::dispatchPass(std::vector <std::string> messageVec){
    std::cout << messageVec.at(0)<< std::endl;
    if (messageVec.size() == 1)
        return(ERR_NEEDMOREPARAMS);
    if (messageVec.size() > 2)
        return(ERR_NEEDLESSPARAMS);
    if (!flags.isRegistered())
        return(ERR_ALREADYREGISTRED);
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
