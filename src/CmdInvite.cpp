#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: Check the following statement: 
//TODO: Because of this line in RFC2812: "There is no requirement that the channel, the target user is being invited to, must exist or be a valid channel."
//TODO: The paramenters are not checked for this
void CommandHandler::cmdInvite(Client *client, AParserResult *result)
{
    if (!client || !result) return;

    ParserResultInvite *result2 = static_cast<ParserResultInvite*>(result);
    const std::vector<std::string> params = result2->getInviteParams();

    const std::string &targetNick = params.at(0);
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

    // If channel is +i (invite-only), only operators may invite
    if (chan->isInviteOnly() && !chan->isOperator(client->getFd()))
    {
        // 482 ERR_CHANOPRIVSNEEDED
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_CHANOPRIVSNEEDED,
                                    chanName + " :You're not channel operator");
        return;
    }

    Client *target = _server.getClientManager().findByNick(targetNick);
    if (!target)
    {
        // 401 ERR_NOSUCHNICK
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOSUCHNICK,
                                    targetNick + " :No such nick/channel");
        return;
    }

    if (chan->isMember(target->getFd()))
    {
        // 443 ERR_USERONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_USERONCHANNEL,
                                    targetNick + " " + chanName + " :is already on channel");
        return;
    }

    // Record invite (so JOIN can check it if +i is set)
    chan->invite(target->getFd());

    // Notify target
    std::string inviteMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                            " INVITE " + targetNick + " :" + chanName + "\r\n";
    MessageSender::sendToClient(target, inviteMsg);

    // Acknowledge to inviter (341 RPL_INVITING)
    MessageSender::sendNumeric(_server.getServerName(), client, RPL_INVITING,
                                targetNick + " " + chanName);
}
