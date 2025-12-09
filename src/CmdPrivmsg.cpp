#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPrivmsg(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 451,
                                   ":You have not registered");
        return;
    }

    ParserResultPrivmsg *res = static_cast<ParserResultPrivmsg*>(result);
    std::vector<std::string> params = res->getPrivmsgParams();

    if (params.size() < 2)
    {
        if (params.empty())
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_NORECIPIENT,
                                       ":No recipient given (PRIVMSG)");
        else
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOTEXTTOSEND,
                                       ":No text to send");
        return;
    }

    const std::string &target = params[0];
    const std::string &message = params[1];

    // Channel message
    if (!target.empty() && target[0] == '#')
    {
        Channel *chan = _server.getChannelManager().findChannel(target);
        if (!chan)
        {
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHCHANNEL,
                                       target + " :No such channel");
            return;
        }
        if (!chan->userExists(client->getFd()))
        {
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOTONCHANNEL,
                                       target + " :You're not on that channel");
            return;
        }

        std::string msg = ":" + client->getPrefix() + " PRIVMSG " + target +
                          " :" + message + "\r\n";
        chan->broadcast(msg); // broadcast to others
    }
    // User message
    else
    {
        Client *receiver = _server.getClientManager().findByNick(target);
        if (!receiver)
        {
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHNICK,
                                       target + " :No such nick");
            return;
        }

        std::string msg = ":" + client->getPrefix() + " PRIVMSG " + target +
                          " :" + message + "\r\n";
        MessageSender::sendToClient(receiver, msg);
    }
}