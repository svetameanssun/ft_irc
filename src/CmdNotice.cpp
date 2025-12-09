#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdNotice(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;
    if (!client->isRegistered())
        return; // No replies for NOTICE

    ParserResultPrivmsg *res = static_cast<ParserResultPrivmsg*>(result);
    std::vector<std::string> params = res->getPrivmsgParams();

    if (params.size() < 2)
        return; // Silently ignore

    const std::string &target = params[0];
    const std::string &message = params[1];

    // Channel message
    if (!target.empty() && target[0] == '#')
    {
        Channel *chan = _server.getChannelManager().findChannel(target);
        if (!chan || !chan->userExists(client->getFd()))
            return; // ignore silently

        std::string msg = ":" + client->getPrefix() + " NOTICE " + target +
                          " :" + message + "\r\n";
        chan->broadcast(msg);
    }
    // User message
    else
    {
        Client *receiver = _server.getClientManager().findByNick(target);
        if (!receiver)
            return; // ignore silently

        std::string msg = ":" + client->getPrefix() + " NOTICE " + target +
                          " :" + message + "\r\n";
        MessageSender::sendToClient(receiver, msg);
    }
}