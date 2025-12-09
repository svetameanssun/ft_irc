
#include "CommandHandler.hpp"
#include "Server.hpp"

/*
//TODO: Very big command, change it into smaller pieces; refactor and adapt the logic 
void CommandHandler::cmdMode(Client *client, AParserResult *result)
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
*/
