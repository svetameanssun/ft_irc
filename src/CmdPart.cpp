
#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPart(Client *client, AParcerResult *result)
{
    if (!client || !result) return;

    //TODO: Change for the good class type
    AParcerResult *result2 = static_cast<ParcerResultPrivmsg*>(result);

    if (result2->getCommand().c_str()[0] != 'P')
    {
        log_err("PART: Not implemented yet");

        //MessageSender::sendNumeric(_server.getServerName(), client, 461,
                                    //"PART :Not enough parameters");
        return;
    }
    //TODO:change this
    std::string chanName = result2->getCommand();
    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan || !chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 442,
                                    chanName + " :You're not on that channel");
        return;
    }

    // Broadcast PART to channel
    std::string partMsg = ":" + client->getNick() + "!" + client->getUser() + "@" +
                          client->getHost() + " PART :" + chanName + "\r\n";
    chan->broadcast(partMsg);

    // Remove from channel
    chan->removeMember(client);

    // If channel is now empty, remove it
    if (chan->isEmpty())
        _server.getChannelManager().removeChannel(chanName);
}