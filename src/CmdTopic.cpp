#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdTopic(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   ERR_NOTREGISTERED, ":You have not registered");
        return;
    }

    ParserResultTopic *result2 = static_cast<ParserResultTopic*>(result);
    const std::vector<std::string> paramsVec = result2->getTopicParams();
    for (std::vector<std::string>::const_iterator it = paramsVec.begin();
        it != paramsVec.end(); it++)
    {
        log_debug("[TOPIC cmd] Parameter[%s]", it->c_str());
    }

    const std::string &chanName = paramsVec.at(0);
    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan)
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   ERR_NOSUCHCHANNEL,
                                   chanName + " :No such channel");
        return;
    }

    if (!chan->isMember(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   ERR_NOTONCHANNEL,
                                   chanName + " :You're not on that channel");
        return;
    }

    // === QUERY TOPIC ===
    if (result2->getTopicMessage().empty())
    {
        if (chan->getTopic().empty())
        {
            //TODO: Implement both cases
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       RPL_NOTOPIC,
                                       chanName + " :No topic is set");
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       RPL_TOPIC,
                                       chanName + " :" + chan->getTopic());
        }
        return;
    }

    // === SET TOPIC ===
    if (chan->isTopicLocked() && !chan->isOperator(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   ERR_CHANOPRIVSNEEDED,
                                   chanName + " :You're not channel operator");
        return;
    }

    chan->setTopic(result2->getTopicMessage());

    std::string msg = ":" + client->getPrefix() +
                      " TOPIC " + chanName +
                      " :" + result2->getTopicMessage() + "\r\n";

    chan->broadcast(msg);
}
