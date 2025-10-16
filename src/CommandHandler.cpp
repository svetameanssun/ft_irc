#include "CommandHandler.hpp"
#include "MessageSender.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "utils.hpp"
#include <sstream>

CommandHandler::CommandHandler(Server &server) : _server(server) {}

//TODO: Maybe break these function into smaller 

// Entry point: dispatch commands
void CommandHandler::execute(Client *client, const std::string &command,
                             const std::vector<std::string> &args)
{
    //Change for switch, or pointers to functions :)
    if (command == "PASS")
        cmdPass(client, args);
    else if (command == "JOIN")
        cmdJoin(client, args);
    else if (command == "NICK")
        cmdNick(client, args);
    else if (command == "USER")
        cmdUser(client, args);
    else if (command == "PRIVMSG")
        cmdPrivmsg(client, args);
    else if (command == "PART")
        cmdPart(client, args);
    else if (command == "QUIT")
        cmdQuit(client, args);
    else if (command == "PING")
        cmdPing(client, args);
    else if (command == "PONG")
        cmdPong(client, args);
    else if (command == "MODE")
        cmdMode(client, args);
    else if (command == "TOPIC")
        cmdTopic(client, args);
    else if (command == "KICK")
        cmdKick(client, args);
    else if (command == "INVITE")
        cmdInvite(client, args);
    else
        MessageSender::sendNumeric(_server.getServerName(), client, 421, command + " :Unknown command");
}

// PASS
void CommandHandler::cmdPass(Client *client, const std::vector<std::string> &args)
{
    if (!client) return;

    if (args.empty())
    {
        // 461 ERR_NEEDMOREPARAMS
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "PASS :Not enough parameters");
        return;
    }

    if (client->isRegistered())
    {
        // 462 ERR_ALREADYREGISTRED
        MessageSender::sendNumeric(_server.getServerName(), client, 462, ":You may not reregister");
        return;
    }

    const std::string& pass = args[0];

    if (!_server.getPassword().empty() && pass != _server.getPassword())
    {
        // 464 ERR_PASSWDMISMATCH
        MessageSender::sendNumeric(_server.getServerName(), client, 464, ":Password incorrect");
        return;
    }

    std::cout << "[DEBUG] PASS accepted for client fd=" << client->getFd() << std::endl;
}


// Implementation: JOIN
void CommandHandler::cmdJoin(Client *client, const std::vector<std::string> &args)
{
    if (args.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "JOIN :Not enough parameters");
        return;
    }

    std::string chanName = args[0];
    std::string key = (args.size() > 1) ? args[1] : "";

    Channel *chan = _server.getChannelManager().findChannel(chanName);

    if (!chan)
    {
        // create new channel
        chan = _server.getChannelManager().addChannel(chanName);
        //chan = _server.findChannel(chanName);
        chan->addMember(client, true); // creator is operator
    }
    else
    {
        // check modes
        if (chan->isInviteOnly() && !chan->isInvited(client->getFd()))
        {
            MessageSender::sendNumeric(_server.getServerName(), client, 473, chanName + " :Cannot join channel (+i)");
            return;
        }
        if (chan->hasKey() && chan->getKey() != key)
        {
            MessageSender::sendNumeric(_server.getServerName(), client, 475, chanName + " :Cannot join channel (+k)");
            return;
        }
        if (chan->getUserLimit() > 0 && chan->getUserCount() >= chan->getUserLimit())
        {
            MessageSender::sendNumeric(_server.getServerName(), client, 471, chanName + " :Cannot join channel (+l)");
            return;
        }
        chan->addMember(client, false);
    }

    // JOIN reply
    std::string joinMsg = ":" + client->getNick() + "!" + client->getUser() + "@" +
                          client->getHost() + " JOIN :" + chanName + "\r\n";
    chan->broadcast(joinMsg);

    // Topic
    if (!chan->getTopic().empty())
        MessageSender::sendNumeric(_server.getServerName(), client, 332, chanName + " :" + chan->getTopic());
    else
        MessageSender::sendNumeric(_server.getServerName(), client, 331, chanName + " :No topic is set");

    // NAMES list
    std::ostringstream oss;
    oss << "= " << chanName << " :";
    const std::map<int, Client*> &members = chan->getChannelMembers(); // add getter in Channel
    for (std::map<int, Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (chan->isOperator(it->first))
            oss << "@" << it->second->getNick() << " ";
        else
            oss << it->second->getNick() << " ";
    }
    MessageSender::sendNumeric(_server.getServerName(), client, 353, oss.str());
    MessageSender::sendNumeric(_server.getServerName(), client, 366, chanName + " :End of /NAMES list");
}

//TODO: ALL THE FUNCTIONS; right now they are copied, we have to adapt logic
void CommandHandler::cmdNick(Client *client, const std::vector<std::string> &args)
{
    if (!client)
        return;

    if (args.empty())
    {
        // 431 ERR_NONICKNAMEGIVEN
        MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
        return;
    }

    const std::string newNick = args[0];

    // check nickname validity basic rules (length > 0). We can add further validation later.
    if (newNick.empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, 431, ":No nickname given");
        return;
    }

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
    if (!client->isRegistered() && !client->getUser().empty())
    {
        client->setRegistered(true);
        // RPL_WELCOME 001
        MessageSender::sendNumeric(_server.getServerName(), client, 1, ":Welcome to the IRC network, " + client->getNick());
        // Optionally send other welcome numerics (002,003,004) per RFC later
    }
}

void CommandHandler::cmdUser(Client *client, const std::vector<std::string> &args)
{
    if (!client) return;

    // We accept a simplified form: USER <username> <realname>
    if (args.size() < 2)
    {
        // 461 ERR_NEEDMOREPARAMS
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "USER :Not enough parameters");
        return;
    }

    const std::string username = args[0];
    const std::string realname = args[1];

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

void CommandHandler::cmdPrivmsg(Client *client, const std::vector<std::string> &args)
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

void CommandHandler::cmdPart(Client *client, const std::vector<std::string> &args)
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


void CommandHandler::cmdQuit(Client *client, const std::vector<std::string> &args)
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


void CommandHandler::cmdPing(Client *client, const std::vector<std::string> &args)
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


void CommandHandler::cmdPong(Client *client, const std::vector<std::string> &args)
{
    if (!client) return;
    // Usually no reply is required
    if (!args.empty()) {
        std::cout << "[DEBUG] Received PONG from " << client->getNick()
                  << " with token: " << args[0] << std::endl;
    }
}
//TODO: Very big command, change it into smaller pieces; refactor and adapt the logic 
void CommandHandler::cmdMode(Client *client, const std::vector<std::string> &args)
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
void CommandHandler::cmdTopic(Client *client, const std::vector<std::string> &args)
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

void CommandHandler::cmdKick(Client* client, const std::vector<std::string>& args)
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

void CommandHandler::cmdInvite(Client *client, const std::vector<std::string> &args)
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
