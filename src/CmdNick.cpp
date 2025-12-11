#include "Server.hpp"
#include "CommandHandler.hpp"

void CommandHandler::cmdNick(Client *client, AParserResult *result)
{
    if (!client || !result)
    {
        log_warning("[Command Handler] cmdNick: No client or no command given");
        return;
    }
    if (!client->getPassAccepted())
    {
        log_warning("[Command Handler] cmdNick: Pass is not accepted. Client cannot do any action");
        return;
    }
    ParserResultNick *result2 = static_cast<ParserResultNick*>(result);

    const std::string newNick = result2->getNickname();
    //It should be done in the parser 
    // check nickname validity basic rules (length > 0). We can add further validation later.
    //if (newNick.empty())
    //{
    //    MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
    //    return;
    //}

    //TODO: check if nick already in use by another client; look at how to validate
    Client *other = _server.getClientManager().findByNick(newNick);
    
    if (other)
    {
        // 436 ERR_NICKCOLLISION
        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_NICKCOLLISION,
                                    newNick + " :Nickname is already in use");
        return;
    }

    std::string oldNick = client->getNick();
    client->setNick(newNick);
    log_debug("[Command Handler] client with fd %d has nickname: %s", client->getFd(), client->getNick().c_str());

    // If the user already had a nick (a rename), broadcast NICK change to channels
    if (!oldNick.empty())
    {
        std::string nickChangeMsg = ":" + oldNick + "!" + client->getUser()
                                    + "@" + client->getHost()
                                    + " NICK :" + newNick + "\r\n";

        _server.getChannelManager().broadcastToJoinedChannels(client->getFd(), nickChangeMsg);
    }

    //If already a USERname and not registered, complete it
    if (!client->isRegistered() && !client->getUser().empty())
    {
        client->setRegistered(true);
        // RPL_WELCOME 001
        MessageSender::sendNumeric(_server.getServerName(), client, RPL_WELCOME,
                                    ":Welcome to the IRC network, " + client->getNick());
        // Optionally send other welcome numerics (002,003,004) per RFC later
    }
}