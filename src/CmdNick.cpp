#include "Server.hpp"
#include "CommandHandler.hpp"

void CommandHandler::cmdNick(Client *client, AParcerResult *result)
{
    if (!client || !result)
        return;

    ParcerResultNick *result2 = static_cast<ParcerResultNick*>(result);

    //Done in the parsing 
    //if (args.empty())
    //{
    //    // 431 ERR_NONICKNAMEGIVEN
    //    MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
    //    return;
    //}

    const std::string newNick = result2->getNickParams().at(0);

    //It should be done in the parser 
    // check nickname validity basic rules (length > 0). We can add further validation later.
    //if (newNick.empty())
    //{
    //    MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
    //    return;
    //}

    // check if nick already in use by another client; look at how to validate
    Client *other = _server.getClientManager().findByFd(client->getFd());
    
    if (other && other != client)
    {
        // 436 ERR_NICKCOLLISION
        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_NICKCOLLISION,
                                    newNick + " :Nickname is already in use");
        return;
    }

    std::string oldNick = client->getNick();
    client->setNick(newNick);

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