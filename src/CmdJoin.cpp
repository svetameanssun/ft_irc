#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdJoin(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   451, ":You have not registered");
        return;
    }

    ParserResultJoin *result2 = static_cast<ParserResultJoin*>(result);

    // Special case: JOIN 0 -> leave all channels
    if (result2->getLeaveAllChansFlag())
    {
        std::vector<std::string> chans = client->getChannels();
        for (size_t i = 0; i < chans.size(); i++)
        {
            Channel *chan = _server.getChannelManager().findChannel(chans[i]);
            if (chan)
                chan->removeMember(client);
        }
        return;
    }
    std::vector<std::string> channels = result2->getJoinChannelsVec();
    std::vector<std::string> keys = result2->getJoinPasswordsVec();

    for (size_t i = 0; i < channels.size(); i++)
    {
        if (client->isChanLimitReached())
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                        ERR_TOOMANYCHANNELS,
                                        channels[i] + " :You have joined too many channels");
            continue;
        }
        const std::string &chanName = channels[i];
        const std::string key = (i < keys.size() ? keys[i] : "");

        if (chanName.empty() || chanName[0] != '#')
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       ERR_BADCHANMASK,
                                       chanName + " :Bad Channel Mask");
            continue;
        }

        Channel *chan = _server.getChannelManager().findChannel(chanName);
        // Create if it doesn't exist
        if (!chan)
        {
            chan = _server.getChannelManager().addChannel(chanName);
            chan->addMember(client, true);
        
            // If a key was provided → channel starts locked
            if (!key.empty())
            {
                chan->setKey(key);
                chan->setKMode(true);
            }
        }
        else
        {
            // Already in channel?
            if (chan->userExists(client->getFd()))
            {
                // Still send topic
                if (!chan->getTopic().empty())
                {
                    MessageSender::sendNumeric(_server.getServerName(), client,
                                               RPL_TOPIC,
                                               chanName + " :" + chan->getTopic());
                }
                else
                {
                    MessageSender::sendNumeric(_server.getServerName(), client,
                                               RPL_NOTOPIC,
                                               chanName + " :No topic is set");
                }
            
                // Still send NAMES
                std::ostringstream oss;
                oss << "= " << chanName << " :";
            
                const std::map<int, Client*> &mem = chan->getChannelMembers();
                for (std::map<int, Client*>::const_iterator it = mem.begin();
                     it != mem.end(); it++)
                {
                    if (chan->isOperator(it->first))
                        oss << "@" << it->second->getNick() << " ";
                    else
                        oss << it->second->getNick() << " ";
                }
            
                MessageSender::sendNumeric(_server.getServerName(), client,
                                           RPL_NAMREPLY, oss.str());
                MessageSender::sendNumeric(_server.getServerName(), client,
                                           RPL_ENDOFNAMES,
                                           chanName + " :End of /NAMES list");
                //BUT do not broadcast it
                continue;
            }
            else
            {
                // Mode checks
                if (chan->isInviteOnly() && !chan->isInvited(client->getFd()))
                {
                    MessageSender::sendNumeric(_server.getServerName(), client,
                                               ERR_INVITEONLYCHAN,
                                               chanName + " :Cannot join channel (+i)");
                    continue;
                }

                if (chan->hasKey() && chan->getKey() != key)
                {
                    MessageSender::sendNumeric(_server.getServerName(), client,
                                               ERR_BADCHANNELKEY,
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
                chan->removeFromInviteList(client->getFd());

            }
        }

        // JOIN broadcast
        std::string joinMsg = ":" + client->getPrefix()
                              + " JOIN " + chanName + "\r\n";
        chan->broadcast(joinMsg);

        // Send topic
        if (!chan->getTopic().empty())
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       RPL_TOPIC,
                                       chanName + " :" + chan->getTopic());
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client,
                                       RPL_NOTOPIC,
                                       chanName + " :No topic is set");
        }

        // Send NAMES
        std::ostringstream oss;
        oss << "= " << chanName << " :";

        const std::map<int, Client*> &mem = chan->getChannelMembers();
        for (std::map<int, Client*>::const_iterator it = mem.begin();
             it != mem.end(); it++)
        {
            if (chan->isOperator(it->first))
                oss << "@" << it->second->getNick() << " ";
            else
                oss << it->second->getNick() << " ";
        }


        MessageSender::sendNumeric(_server.getServerName(), client,
                                   RPL_NAMREPLY, oss.str());
        
        MessageSender::sendNumeric(_server.getServerName(), client,
                                   RPL_ENDOFNAMES,
                                   chanName + " :End of /NAMES list");
    }
}
