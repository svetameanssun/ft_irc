#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdKick(Client *client, AParcerResult *result)
{
    if (!client || !result) return;

    ParcerResultKick *result2 = static_cast<ParcerResultKick*>(result);

    const std::vector<std::string> params = result2->getKickParams();
    if (params.size() < 2)
    {
        // 461 ERR_NEEDMOREPARAMS
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NEEDMOREPARAMS,
                                    "KICK :Not enough parameters");
        return;
    }

    //TODO: be sure which one is in which position
    const std::string &chanName = params.at(0);
    const std::string &targetNick = params.at(1);
    std::string reason = (params.size() > 2) ? params.at(2) : "Kicked";

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

    if (!chan->isOperator(client->getFd()))
    {
        // 482 ERR_CHANOPRIVSNEEDED
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_CHANOPRIVSNEEDED,
                                    chanName + " :You're not channel operator");
        return;
    }

    Client *target = _server.getClientManager().findByNick(targetNick);
    if (!target || !chan->isMember(target->getFd()))
    {
        // 441 ERR_USERNOTINCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_USERNOTINCHANNEL,
                                   targetNick + " " + chanName + " :They aren't on that channel");
        return;
    }

    // Broadcast KICK message
    std::string kickMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                          " KICK " + chanName + " " + targetNick + " :" + reason + "\r\n";
    chan->broadcast(kickMsg);

    // Remove the target
    chan->removeMember(target);

    if (chan->isEmpty()) { _server.getChannelManager().removeChannel(chanName); }
}
