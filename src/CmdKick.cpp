#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdKick(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered()) {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   ERR_NOTREGISTERED,
                                   ":You have not registered");
        return;
    }

    ParserResultKick *result2 = static_cast<ParserResultKick*>(result);
    const std::map<int,std::vector<std::string> > paramsMap = result2->getKickParamsMap();

    for (size_t i = 0; i < paramsMap.size(); ++i)
    {
        const std::vector<std::string> paramsVec = paramsMap.at(0);
        const std::string &chanName  = paramsVec.at(0);
        const std::string &targetNick = paramsVec.at(1);
        
        std::string reason = (!result2->getKickComment().empty()
                                ? result2->getKickComment() : "Kicked");

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

        if (!chan->isOperator(client->getFd())) {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       ERR_CHANOPRIVSNEEDED,
                                       chanName + " :You're not channel operator");
            return;
        }

        Client *target = _server.getClientManager().findByNick(targetNick);
        if (!target || !chan->isMember(target->getFd())) {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       ERR_USERNOTINCHANNEL,
                                       targetNick + " " + chanName +
                                       " :They aren't on that channel");
            return;
        }

        // Build and broadcast KICK message
        std::string kickMsg = ":" + client->getPrefix() +
                              " KICK " + chanName + " " + targetNick +
                              " :" + reason + "\r\n";

        chan->broadcast(kickMsg);

        // Remove target from channel
        chan->removeMember(target);

        // Remove empty channel
        if (chan->isEmpty()) { _server.getChannelManager().removeChannel(chanName); }
    }  
}
