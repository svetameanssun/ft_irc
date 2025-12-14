#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: I do not actually know which parameter is the topic
//TODO: Adapt logic so it is only done by operators of the channel
void CommandHandler::cmdTopic(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   451, ":You have not registered");
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
                      " :" + "\r\n"; //result2->getTopic() + "\r\n";

    chan->broadcast(msg);
}
