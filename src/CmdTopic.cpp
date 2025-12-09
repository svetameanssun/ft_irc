#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: Adapt logic so it is only done by operators of the channel
void CommandHandler::cmdTopic(Client *client, AParserResult *result)
{
    if (!client || !result) return;

    ParserResultTopic *result2 = static_cast<ParserResultTopic*>(result);
    const std::vector<std::string> params = result2->getTopicParams();
    if (params.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NEEDMOREPARAMS,
                                    "TOPIC :Not enough parameters");
        return;
    }

    //TODO: Check which parameter is the channame
    const std::string &chanName = params.at(1);

    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan)
    {
        // 403 ERR_NOSUCHCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHCHANNEL,
                                    chanName + " :No such channel");
        return;
    }

    if (!chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOTONCHANNEL,
                                    chanName + " :You're not on that channel");
        return;
    }

    // --- Query topic ---
    //TODO: Check how many parameters do we usually have
    if (params.size() == 2)
    {
        if (chan->getTopic().empty())
            MessageSender::sendNumeric(_server.getServerName(), client, RPL_NOTOPIC,
                                        chanName + " :No topic is set");
        else
            MessageSender::sendNumeric(_server.getServerName(), client, RPL_TOPIC,
                                        chanName + " :" + chan->getTopic());
        return;
    }

    // --- Set topic ---
    //TODO: Check the order and the number of arguments to see the position of the topic
    std::string newTopic = params.at(3);
    chan->setTopic(newTopic);

    // Broadcast topic change to channel
    std::string topicMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                           " TOPIC " + chanName + " :" + newTopic + "\r\n";
    chan->broadcast(topicMsg);
}
