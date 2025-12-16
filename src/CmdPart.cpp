#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPart(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        MessageSender::sendNumeric(_server.getServerName(),
                                   client, 451,
                                   ":You have not registered");
        return;
    }

    ParserResultPart *result2 = static_cast<ParserResultPart*>(result);

    // Multiple channels allowed: PART #a,#b,#c :optional message
    const std::vector<std::string> &channels = result2->getPartChannelsVec();
    const std::string &comment = result2->getPartMessage();

    if (channels.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(),
                                   client, ERR_NEEDMOREPARAMS,
                                   "PART :Not enough parameters");
        return;
    }

    for (size_t i = 0; i < channels.size(); i++)
    {
        const std::string &chanName = channels[i];

        Channel *chan = _server.getChannelManager().findChannel(chanName);
        if (!chan)
        {
            MessageSender::sendNumeric(_server.getServerName(),
                                       client, ERR_NOSUCHCHANNEL,
                                       chanName + " :No such channel");
            continue;
        }

        if (!chan->userExists(client->getFd()))
        {
            MessageSender::sendNumeric(_server.getServerName(),
                                       client, ERR_NOTONCHANNEL,
                                       chanName + " :You're not on that channel");
            continue;
        }

        // Build PART message
        std::string partMsg = ":" + client->getPrefix()
                              + " PART " + chanName;

        if (!comment.empty())
            partMsg += " :" + comment;

        partMsg += "\r\n";

        // Send to others in channel
        chan->broadcast(partMsg);

        // Remove user
        chan->removeMember(client);

        // If channel empty → delete it
        if (chan->isEmpty())
            _server.getChannelManager().removeChannel(chanName);
    }
}
