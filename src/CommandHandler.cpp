#include "CommandHandler.hpp"
#include "Server.hpp"
#include "Channel.hpp"

CommandHandler::CommandHandler(Server &server) : _server(server) {}

//TODO: Maybe break these function into smaller 
//TODO: ALL THE FUNCTIONS; right now they are copied, we have to adapt logic
//TODO: We need to review each of them to check that everything works as intended
//TODO: See if all the commands match with the specification of the subject and the partner has the same


// Entry point: dispatch commands
void CommandHandler::execute(Client *client, const std::string &command, AParcerResult *result)
{
    //TODO:Change for switch, or pointers to functions :)
    if (command == "PASS")
        cmdPass(client, result);
    else if (command == "NICK")
        cmdNick(client, result);
    else if (command == "USER")
        cmdUser(client, result);
    else if (command == "JOIN")
        cmdJoin(client, result);
    //else if (command == "PRIVMSG")
    //    cmdPrivmsg(client, result);
    //else if (command == "PART")
    //    cmdPart(client, result);
    //else if (command == "QUIT")
    //    cmdQuit(client, result);
    //else if (command == "PING")
    //    cmdPing(client, result);
    //else if (command == "PONG")
    //    cmdPong(client, result);
    //else if (command == "MODE")
    //    cmdMode(client, result);
    //else if (command == "TOPIC")
    //    cmdTopic(client, result);
    //else if (command == "KICK")
    //    cmdKick(client, result);
    //else if (command == "INVITE")
    //    cmdInvite(client, result);
    else
        MessageSender::sendNumeric(_server.getServerName(), client, 421, command + " :Unknown command");
}

// PASS
void CommandHandler::cmdPass(Client *client, AParcerResult *result)
{
    if (!client || !result) return;
    
    ParcerResultPass *result2 = static_cast<ParcerResultPass*>(result);
    
    if (client->isRegistered())
    {
        // 462 ERR_ALREADYREGISTRED
        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_ALREADYREGISTRED,
                                    ":You may not reregister");
        return;
    }

    std::vector<std::string> params = result2->getPassParams();

    const std::string &pass = params.at(0);

    if (!_server.getPassword().empty() && pass != _server.getPassword())
    {
        //TODO: the RFC does not specify this, but to me it is pretty logic to implement it
        // 464 ERR_PASSWDMISMATCH
        client->setPassAccepted(false);
        log_debug("Password not correct, user cannot register");

        MessageSender::sendNumeric(_server.getServerName(),
                                    client, ERR_PASSWDMISMATCH,
                                    ":Password incorrect");
        return;
    }

    client->setPassAccepted(true);
    log_debug("PASS accepted for client fd=%d", client->getFd());
}


// Implementation: JOIN
void CommandHandler::cmdJoin(Client *client, AParcerResult *result)
{
    if (!client || !result)
        return;

    if (!client->isRegistered())
    {
        //TODO: No available error for "not registered user"
        MessageSender::sendNumeric(_server.getServerName(), client, 451,
                                   ":You have not registered");
        return;
    }

    ParcerResultJoin *result2 = static_cast<ParcerResultJoin*>(result);

    //Should be done by the parser
    //if (args.empty())
    //{
    //    MessageSender::sendNumeric(_server.getServerName(), client, 461, "JOIN :Not enough parameters");
    //    return;
    //}
    //TODO: Can have multiple channels, we need to adapt the logic; right now it is made for just one channel
    const std::map<std::string, std::string> &joinParams = result2->getJoinParamsMap();
    
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
    //TODO: refactor this function and create a join_aux file
    // ✅ Iterate over channel,key pairs
    for (std::map<std::string, std::string>::const_iterator it = joinParams.begin();
         it != joinParams.end(); ++it)
    {
        const std::string &key = it->first;
        const std::string &chanName = it->second;

        // ✅ Validate channel name format
        if (chanName.empty() || chanName[0] != '#')
        {
            MessageSender::sendNumeric(_server.getServerName(), client, ERR_BADCHANMASK,
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
                    MessageSender::sendNumeric(_server.getServerName(), client, ERR_INVITEONLYCHAN,
                                               chanName + " :Cannot join channel (+i)");
                    continue;
                }
                if (chan->hasKey() && chan->getKey() != key)
                {
                    MessageSender::sendNumeric(_server.getServerName(), client, ERR_BADCHANNELKEY,
                                               chanName + " :Cannot join channel (+k)");
                    continue;
                }
                if (chan->getUserLimit() > 0 &&
                    chan->getUserCount() >= chan->getUserLimit())
                {
                    MessageSender::sendNumeric(_server.getServerName(), client, ERR_CHANNELISFULL,
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
            MessageSender::sendNumeric(_server.getServerName(), client, RPL_TOPIC,
                                       chanName + " :" + chan->getTopic());
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client, RPL_NOTOPIC,
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

        MessageSender::sendNumeric(_server.getServerName(), client, RPL_NAMREPLY, oss.str());
        MessageSender::sendNumeric(_server.getServerName(), client, RPL_ENDOFNAMES,
                                   chanName + " :End of /NAMES list");

        // ✅ Remove invite after success
        chan->removeFromInviteList(client->getFd());
    }
}

void CommandHandler::cmdNick(Client *client, AParcerResult *result)
{
    if (!client || !result)
        return;

    ParcerResultNick *result2 = static_cast<ParcerResultNick*>(result);

    //Done in the parsing 
    //if (args.empty())
    //{
    //    // 431 ERR_NONICKNAMEGIVEN
    //    MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
    //    return;
    //}

    const std::string newNick = result2->getNickParams().at(0);

    //It should be done in the parser 
    // check nickname validity basic rules (length > 0). We can add further validation later.
    //if (newNick.empty())
    //{
    //    MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
    //    return;
    //}

    // check if nick already in use by another client; look at how to validate
    Client *other = _server.getClientManager().findByNick(newNick);
    if (other && other != client)
    {
        // 433 ERR_NICKNAMEINUSE
        MessageSender::sendNumeric(_server.getServerName(), client, 433, newNick + " :Nickname is already in use");
        return;
    }

    std::string oldNick = client->getNick();
    client->setNick(newNick);

    // If the user already had a nick (a rename), broadcast NICK change to channels
    if (!oldNick.empty())
    {
        std::string nickChangeMsg = ":" + oldNick + "!" + client->getUser() + "@" + client->getHost()
                                 + " NICK :" + newNick + "\r\n";
        _server.getChannelManager().broadcastToJoinedChannels(client->getFd(), nickChangeMsg);
    }

    // If both NICK and USER are set and client not registered, complete registration
    if (!client->isRegistered()) // && !client->getUser().empty())
    {
        client->setRegistered(true);
        client->setNick(newNick);
        // RPL_WELCOME 001
        MessageSender::sendNumeric(_server.getServerName(), client, 1, ":Welcome to the IRC network, " + client->getNick());
        // Optionally send other welcome numerics (002,003,004) per RFC later
    }
}

void CommandHandler::cmdUser(Client *client, AParcerResult *result)
{
    ParcerResultUser *result2 = static_cast<ParcerResultUser*>(result);
    if (!client) return;

    //It should be done in the parser 
    // We accept a simplified form: USER <username> <realname>
    //if (args.size() < 2)
    //{
    //    // 461 ERR_NEEDMOREPARAMS
    //    MessageSender::sendNumeric(_server.getServerName(), client, 461, "USER :Not enough parameters");
    //    return;
    //}

    const std::string username = result2->getUserParams().at(0);
    const std::string realname = result2->getUserParams().at(1);

    client->setUser(username);
    client->setRealName(realname);

    // If both NICK and USER are set and client not registered, complete registration
    if (!client->isRegistered() && !client->getNick().empty())
    {
        client->setRegistered(true);
        // RPL_WELCOME 001
        MessageSender::sendNumeric(_server.getServerName(), client, 1, ":Welcome to the IRC network, " + client->getNick());
        // Optionally send other welcome numerics (002,003,004)
    }
}

/*void CommandHandler::cmdPrivmsg(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.size() < 2) {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "PRIVMSG :Not enough parameters");
        return;
    }

    const std::string &target = args[0];
    const std::string &message = args[1];

    // Message format
    std::string msg = ":" + client->getNick() + "!" + client->getUser() + "@" +
                      client->getHost() + " PRIVMSG " + target + " :" + message + "\r\n";

    if (!target.empty() && target[0] == '#')
    {
        // Channel target
        Channel *chan = _server.getChannelManager().findChannel(target);
        if (!chan)
        {
            // 403 ERR_NOSUCHCHANNEL
            MessageSender::sendNumeric(_server.getServerName(), client, 403, target + " :No such channel");
            return;
        }
        if (!chan->isMember(client->getFd()))
        {
            // 442 ERR_NOTONCHANNEL
            MessageSender::sendNumeric(_server.getServerName(), client, 442, target + " :You're not on that channel");
            return;
        }
        // Broadcast to channel, excluding sender
        chan->broadcast(msg);//, client->getFd());
    }
    else
    {
        // User target
        Client *dest = _server.getClientManager().findByNick(target);
        if (!dest)
        {
            // 401 ERR_NOSUCHNICK
            MessageSender::sendNumeric(_server.getServerName(), client, 401, target + " :No such nick/channel");
            return;
        }
        MessageSender::sendToClient(dest, msg);
    }
}

void CommandHandler::cmdPart(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "PART :Not enough parameters");
        return;
    }

    std::string chanName = args[0];
    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan || !chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 442, chanName + " :You're not on that channel");
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


void CommandHandler::cmdQuit(Client *client, AParcerResult *result)
{
    if (!client) return;

    std::string quitMsg = "Client Quit";
    if (!args.empty())
        quitMsg = args[0];

    // Build quit message
    std::string msg = ":" + client->getNick() + "!" + client->getUser() + "@" +
                      client->getHost() + " QUIT :" + quitMsg + "\r\n";

    // Broadcast QUIT to all channels
    _server.getChannelManager().broadcastToJoinedChannels(client->getFd(), msg);

    // Remove client from channels
    _server.getChannelManager().removeClientFromChannels(client);
    
    // Remove client from server
    _server.getClientManager().removeClient(client->getFd());
}


void CommandHandler::cmdPing(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.empty())
    {
        // 409 ERR_NOORIGIN
        MessageSender::sendNumeric(_server.getServerName(), client, 409, ":No origin specified");
        return;
    }

    const std::string& token = args[0];
    std::string pongMsg = ":" + _server.getServerName() + " PONG " + _server.getServerName() +
                          " :" + token + "\r\n";
    MessageSender::sendToClient(client, pongMsg);
}


void CommandHandler::cmdPong(Client *client, AParcerResult *result)
{
    if (!client) return;
    // Usually no reply is required
    if (!args.empty()) {
        std::cout << "[DEBUG] Received PONG from " << client->getNick()
                  << " with token: " << args[0] << std::endl;
    }
}
//TODO: Very big command, change it into smaller pieces; refactor and adapt the logic 
void CommandHandler::cmdMode(Client *client, AParcerResult *result)
{
    if (!client)
        return;

    if (args.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE :Not enough parameters");
        return;
    }

    const std::string &target = args[0];

    // ===============================================
    // USER MODES
    // ===============================================
    if (target[0] != '#')
    {
        // Only server can grant +o (IRC operator)
        if (args.size() == 1)
        {
            // Query user mode
            std::string modes = client->isOperator() ? "+o" : "";
            MessageSender::sendNumeric(_server.getServerName(), client, 221, client->getNick() + " " + modes);
            return;
        }

        const std::string &modeStr = args[1];
        if (modeStr.find('o') != std::string::npos)
        {
            // Users cannot set themselves as IRC operators //TODO: it needs to ignore silently
            MessageSender::sendNumeric(_server.getServerName(), client, 481, ":Permission Denied - You're not an IRC operator");
        }
        else
        {
            MessageSender::sendNumeric(_server.getServerName(), client, 472, modeStr + " :Unknown mode flag");
        }
        return;
    }

    // ===============================================
    // CHANNEL MODES
    // ===============================================
    Channel *chan = _server.getChannelManager().findChannel(target);
    if (!chan)
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 403, target + " :No such channel");
        return;
    }

    // Query channel modes
    if (args.size() == 1)
    {
        std::string modeStr = "+";
        if (chan->isInviteOnly()) modeStr += "i";
        if (chan->isTopicLocked()) modeStr += "t";
        if (chan->hasKey()) modeStr += "k";
        if (chan->hasLimit() > 0) modeStr += "l";
        // +o not listed since it applies to specific users
        MessageSender::sendNumeric(_server.getServerName(), client, 324, chan->getName() + " " + modeStr);
        return;
    }

    // Must be operator to modify modes
    if (!chan->isMember(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 442, target + " :You're not on that channel");
        return;
    }
    if (!chan->isOperator(client->getFd()))
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 482, target + " :You're not channel operator");
        return;
    }

    // --- Parse and apply modes ---
    const std::string &modeStr = args[1];
    bool adding = true;
    size_t argIndex = 2;

    for (size_t i = 0; i < modeStr.size(); ++i)
    {
        char mode = modeStr[i];
        if (mode == '+') { adding = true; continue; }
        if (mode == '-') { adding = false; continue; }

        switch (mode)
        {
            case 'i':
                chan->setInviteOnly(adding);
                break;

            case 't':
                chan->setTMode(adding);
                break;

            case 'k':
                if (adding)
                {
                    if (argIndex >= args.size())
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +k :Not enough parameters");
                        return;
                    }
                    chan->setKey(args[argIndex++]);
                }
                else
                {
                    chan->setKey("");
                }
                break;

            case 'o':
                if (argIndex >= args.size())
                {
                    MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +o :Not enough parameters");
                    return;
                }
                {
                    std::string targetNick = args[argIndex++];
                    Client *targetClient = _server.getClientManager().findByNick(targetNick);
                    if (!targetClient || !chan->isMember(targetClient->getFd()))
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 441, targetNick + " " + chan->getName() + " :They aren't on that channel");
                        return;
                    }
                    if (adding)
                        chan->promoteToOp(targetClient->getFd());
                    else
                        chan->demoteFromOp(targetClient->getFd());
                }
                break;

            case 'l':
                if (adding)
                {
                    if (argIndex >= args.size())
                    {
                        MessageSender::sendNumeric(_server.getServerName(), client, 461, "MODE +l :Not enough parameters");
                        return;
                    }
                    int limit = std::atoi(args[argIndex++].c_str());
                    if (limit <= 0)
                        limit = 0;
                    chan->setUserLimit(limit);
                }
                else
                {
                    chan->setUserLimit(0);
                }
                break;

            default:
                MessageSender::sendNumeric(_server.getServerName(), client, 472, std::string(1, mode) + " :is unknown mode char to me");
                break;
        }
    }

    // Broadcast the final mode change to the channel
    std::ostringstream oss;
    oss << ":" << client->getNick() << "!" << client->getUser() << "@" << client->getHost()
        << " MODE " << target << " " << modeStr;
    // Append arguments used (if any)
    for (size_t j = 2; j < args.size(); ++j)
        oss << " " << args[j];
    oss << "\r\n";

    chan->broadcast(oss.str());
}

//TODO: Adapt logic so it is only done by operators of the channel
void CommandHandler::cmdTopic(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "TOPIC :Not enough parameters");
        return;
    }

    const std::string &chanName = args[0];
    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan)
    {
        // 403 ERR_NOSUCHCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 403, chanName + " :No such channel");
        return;
    }

    if (!chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 442, chanName + " :You're not on that channel");
        return;
    }

    // --- Query topic ---
    if (args.size() == 1)
    {
        if (chan->getTopic().empty())
            MessageSender::sendNumeric(_server.getServerName(), client, 331, chanName + " :No topic is set");
        else
            MessageSender::sendNumeric(_server.getServerName(), client, 332, chanName + " :" + chan->getTopic());
        return;
    }

    // --- Set topic ---
    std::string newTopic = args[1];
    chan->setTopic(newTopic);

    // Broadcast topic change to channel
    std::string topicMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                           " TOPIC " + chanName + " :" + newTopic + "\r\n";
    chan->broadcast(topicMsg);
}

void CommandHandler::cmdKick(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.size() < 2) {
        // 461 ERR_NEEDMOREPARAMS
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "KICK :Not enough parameters");
        return;
    }

    const std::string &chanName = args[0];
    const std::string &targetNick = args[1];
    std::string reason = (args.size() > 2) ? args[2] : "Kicked";

    Channel *chan = _server.getChannelManager().findChannel(chanName);
    if (!chan)
    {
        // 403 ERR_NOSUCHCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 403, chanName + " :No such channel");
        return;
    }

    if (!chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 442, chanName + " :You're not on that channel");
        return;
    }

    if (!chan->isOperator(client->getFd()))
    {
        // 482 ERR_CHANOPRIVSNEEDED
        MessageSender::sendNumeric(_server.getServerName(), client, 482, chanName + " :You're not channel operator");
        return;
    }

    Client *target = _server.getClientManager().findByNick(targetNick);
    if (!target || !chan->isMember(target->getFd()))
    {
        // 441 ERR_USERNOTINCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 441,
                                   targetNick + " " + chanName + " :They aren't on that channel");
        return;
    }

    // Broadcast KICK message
    std::string kickMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                          " KICK " + chanName + " " + targetNick + " :" + reason + "\r\n";
    chan->broadcast(kickMsg);

    // Remove the target
    chan->removeMember(target);

    if (chan->isEmpty())
    {
        _server.getChannelManager().removeChannel(chanName);
    }
}

void CommandHandler::cmdInvite(Client *client, AParcerResult *result)
{
    if (!client) return;

    if (args.size() < 2)
    {
        // 461 ERR_NEEDMOREPARAMS
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "INVITE :Not enough parameters");
        return;
    }

    const std::string &targetNick = args[0];
    const std::string &chanName = args[1];

    Channel *chan = _server.getChannelManager().findChannel(chanName);
    if (!chan)
    {
        // 403 ERR_NOSUCHCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 403, chanName + " :No such channel");
        return;
    }

    if (!chan->isMember(client->getFd()))
    {
        // 442 ERR_NOTONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 442, chanName + " :You're not on that channel");
        return;
    }

    // If channel is +i (invite-only), only operators may invite
    if (chan->isInviteOnly() && !chan->isOperator(client->getFd()))
    {
        // 482 ERR_CHANOPRIVSNEEDED
        MessageSender::sendNumeric(_server.getServerName(), client, 482, chanName + " :You're not channel operator");
        return;
    }

    Client *target = _server.getClientManager().findByNick(targetNick);
    if (!target)
    {
        // 401 ERR_NOSUCHNICK
        MessageSender::sendNumeric(_server.getServerName(), client, 401, targetNick + " :No such nick/channel");
        return;
    }

    if (chan->isMember(target->getFd()))
    {
        // 443 ERR_USERONCHANNEL
        MessageSender::sendNumeric(_server.getServerName(), client, 443, targetNick + " " + chanName + " :is already on channel");
        return;
    }

    // Record invite (so JOIN can check it if +i is set)
    chan->invite(target->getFd());

    // Notify target
    std::string inviteMsg = ":" + client->getNick() + "!" + client->getUser() + "@" + client->getHost() +
                            " INVITE " + targetNick + " :" + chanName + "\r\n";
    MessageSender::sendToClient(target, inviteMsg);

    // Acknowledge to inviter (341 RPL_INVITING)
    MessageSender::sendNumeric(_server.getServerName(), client, 341, targetNick + " " + chanName);
}
*/