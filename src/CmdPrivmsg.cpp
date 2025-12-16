#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: It is a copy of "Notice" but responding to errors; if we modify "Notice", we need to modify this

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

    ParserResultPrivmsg *result2 = static_cast<ParserResultPrivmsg*>(result);
    std::vector<std::string> params = result2->getPrivmsgParams();

    const std::string &target = params[0];
    const std::string &message = params[1];
    const std::string &message2 = result2->getPrivmsgMessage();
    log_debug("Message from paramsVecPrivMsg: %s", message.c_str());
    log_debug("Message from getPrivMsg: %s", message2.c_str());


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
        chan->broadcast(msg);
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