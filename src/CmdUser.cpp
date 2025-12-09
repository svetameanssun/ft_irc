#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdUser(Client *client, AParserResult *result)
{
    if (!client || !result) return;
    
    ParserResultUser *result2 = static_cast<ParserResultUser*>(result);
    

    //It should be done in the parser 
    // We accept a simplified form: USER <username> <realname>
    //if (args.size() < 2)
    //{
    //    // 461 ERR_NEEDMOREPARAMS
    //    MessageSender::sendNumeric(_server.getServerName(), client, 461, "USER :Not enough parameters");
    //    return;
    //}

    std::cout << "=================== PARAMS FROM USER COMMAND =====================" << std::endl;
    if (result2)
        result2->printResult();
    else 
        return log_err("No args here");
    std::cout << "==================================================================" << std::endl;
    const std::string username = result2->getUserParams().at(0);
    const std::string realname = result2->getUserParams().at(1);

    client->setUser(username);
    client->setRealName(realname);

    //If already a NICK and is not registered, complete it
    if (!client->isRegistered() && !client->getNick().empty())
    {
        client->setRegistered(true);
        // RPL_WELCOME 001
        MessageSender::sendNumeric(_server.getServerName(), client, RPL_WELCOME,
                                    ":Welcome to the IRC network, " + client->getNick());
        // Optionally send other welcome numerics (002,003,004)
    }
}