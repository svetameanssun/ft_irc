#include "CommandHandler.hpp"
#include "Server.hpp"

// Implementation: JOIN
void CommandHandler::cmdJoin(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        //TODO: No available error for "not registered user"
        MessageSender::sendNumeric(_server.getServerName(),
                                    client, 451,
                                   ":You have not registered");
        return;
    }

    ParserResultJoin *result2 = static_cast<ParserResultJoin*>(result);

    //Should be done by the parser
    //if (args.empty())
    //{
    //    MessageSender::sendNumeric(_server.getServerName(), client, 461, "JOIN :Not enough parameters");
    //    return;
    //}
    //TODO: Can have multiple channels, we need to adapt the logic; right now it is made for just one channel
    const std::vector<std::string> &joinParams = result2->getJoinParamsVec();
    
    //// ✅ Special case: JOIN 0 → leave all channels
    //if (joinParams.size() == 1 && joinParams.begin()->first == "0")
    //{
    //    std::vector<std::string> chanNames =
    //        _server.getClientManager().findByFd(client->getFd())->getChannels();
//
    //    for (size_t i = 0; i < chanNames.size(); i++)
    //    {
    //        Channel *chan = _server.getChannelManager().findChannel(chanNames[i]);
    //        if (chan)
    //            chan->removeMember(client);
    //    }
    //    return;
    //}
    // ✅ Iterate over channel,key pairs
    /*for (std::vector<std::string>::const_iterator it = joinParams.begin();
         it != joinParams.end(); ++it)
    {
        const std::string &key = it->first;
        const std::string &chanName = it->second;

        // ✅ Validate channel name format
        if (chanName.empty() || chanName[0] != '#')
        {
            MessageSender::sendNumeric(_server.getServerName(),
                                       client, ERR_BADCHANMASK,
                                       chanName + " :Bad Channel Mask");
            continue;
        }

        Channel *chan = _server.getChannelManager().findChannel(chanName);

        if (!chan)
        {
            chan = _server.getChannelManager().addChannel(chanName);
            chan->addMember(client, true); // Creator is operator
        }
        else
        {
            // ✅ Check mode restrictions
            if (chan->userExists(client->getFd()))
            {
                //TODO: implement this
                // Already joined → still reply NAMES & topic
                // RFC allows re-send of JOIN message
            }
            else
            {
                if (chan->isInviteOnly() && !chan->isInvited(client->getFd()))
                {
                    MessageSender::sendNumeric(_server.getServerName(),
                                                client, ERR_INVITEONLYCHAN,
                                                chanName + " :Cannot join channel (+i)");
                    continue;
                }
                if (chan->hasKey() && chan->getKey() != key)
                {
                    MessageSender::sendNumeric(_server.getServerName(),
                                                client, ERR_BADCHANNELKEY,
                                                chanName + " :Cannot join channel (+k)");
                    continue;
                }
                if (chan->getUserLimit() > 0 &&
                    chan->getUserCount() >= chan->getUserLimit())
                {
                    MessageSender::sendNumeric(_server.getServerName(), client,
                                                ERR_CHANNELISFULL,
                                                chanName + " :Cannot join channel (+l)");
                    continue;
                }

                chan->addMember(client, false);
            }
        }

        // ✅ JOIN broadcast
        std::string joinMsg = ":" + client->getPrefix() +
                              " JOIN " + chanName + "\r\n";
        chan->broadcast(joinMsg);

        //TODO: Look if this is necessary
        // ✅ Send topic (related numerics)
        if (!chan->getTopic().empty())
        {
            MessageSender::sendNumeric(_server.getServerName(),
                                        client, RPL_TOPIC,
                                        chanName + " :" + chan->getTopic());
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                        RPL_NOTOPIC,
                                        chanName + " :No topic is set");
        }

        //TODO: Check if this is necessary
        // ✅ Send names list (353 + 366)
        std::ostringstream oss;
        oss << "= " << chanName << " :";

        const std::map<int, Client*> &members = chan->getChannelMembers();
        for (std::map<int, Client*>::const_iterator m = members.begin();
             m != members.end(); m++)
        {
            if (chan->isOperator(m->first))
                oss << "@" << m->second->getNick() << " ";
            else
                oss << m->second->getNick() << " ";
        }

        MessageSender::sendNumeric(_server.getServerName(),
                                    client, RPL_NAMREPLY, oss.str());

        MessageSender::sendNumeric(_server.getServerName(),
                                    client, RPL_ENDOFNAMES,
                                    chanName + " :End of /NAMES list");

        // ✅ Remove invite after success
        chan->removeFromInviteList(client->getFd());
    }
        */
    log_err("CmdJoin not implemented");
}