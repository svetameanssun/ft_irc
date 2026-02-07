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
        if (result2->isTopicQuery())
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
        else
        {
            if (chan->isTopicLocked() && !chan->isOperator(client->getFd()))
            {
                MessageSender::sendNumeric(_server.getServerName(), client,
                                           ERR_CHANOPRIVSNEEDED,
                                           chanName + " :You're not channel operator");
                return;
            }
            chan->setTopic("");

            std::string msg = ":" + client->getPrefix() +
                              " TOPIC " + chanName + " \r\n";

            chan->broadcast(msg);
            return;
        }
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
    log_warning("Topic message: %s", chan->getTopic().c_str());
    std::string msg = ":" + client->getPrefix() +
                      " TOPIC " + chanName; // +
                      //" :" + result2->getTopicMessage() + "\r\n";

    if (result2->getTopicMessage().at(0) != ':')
        msg += " :";
    else
        msg += " ";
    msg += result2->getTopicMessage() + "\r\n";

    chan->broadcast(msg);
}
