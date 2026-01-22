#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdUser(Client *client, AParserResult *result)
{
    if (!client || !result)
    {
        log_warning("[Command Handler] cmdUser: No client or no command given");
        return;
    }
    
    if (!client->getPassAccepted())
    {
        log_warning("[Command Handler] cmdUser: Pass is not accepted. Client cannot do any action");
        return; 
    }

    ParserResultUser *result2 = static_cast<ParserResultUser*>(result);

    if (result2)
    {
        log_debug("[Command Handler] cmdUser: ");
        result2->printResult();
    }
    else 
        return log_warning("[Command Handler] cmdUser: No args");

    const std::string username = result2->getUsername(); //[RUBEN] I (sveta) have changed _nickname to _username changed this
    const std::string realname = result2->getRealname();

    client->setUser(username);
    client->setRealName(realname);
    
    log_debug("User: %s with realname: %s and nickname: %s", username.c_str(), realname.c_str(), result2->getUsername().c_str());

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