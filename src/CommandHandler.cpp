#include "CommandHandler.hpp"
#include "MessageSender.hpp"
#include "Channel.hpp"
#include <sstream>

CommandHandler::CommandHandler(Server& server) : _server(server) {}

// Entry point: dispatch commands
void CommandHandler::execute(Client* client, const std::string& command,
                             const std::vector<std::string>& args) {
    if (command == "JOIN")
        cmdJoin(client, args);
    else {
        MessageSender::sendNumeric(_server.getServerName(), client, 421, command + " :Unknown command");
    }
}

// Implementation: JOIN
void CommandHandler::cmdJoin(Client* client, const std::vector<std::string>& args) {
    if (args.empty()) {
        MessageSender::sendNumeric(_server.getServerName(), client, 461, "JOIN :Not enough parameters");
        return;
    }

    std::string chanName = args[0];
    std::string key = (args.size() > 1) ? args[1] : "";

    Channel *chan = _server.findChannel(chanName);

    if (!chan) {
        // create new channel
        chan = _server.addChannel(chanName);
        //chan = _server.findChannel(chanName);
        chan->addMember(client, true); // creator is operator
    } else {
        // check modes
        if (chan->isInviteOnly() && !chan->isInvited(client->getFd())) {
            MessageSender::sendNumeric(_server.getServerName(), client, 473, chanName + " :Cannot join channel (+i)");
            return;
        }
        if (chan->hasKey() && chan->getKey() != key) {
            MessageSender::sendNumeric(_server.getServerName(), client, 475, chanName + " :Cannot join channel (+k)");
            return;
        }
        if (chan->getUserLimit() > 0 && chan->getUserCount() >= chan->getUserLimit()) {
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
    const std::map<int, Client*>& members = chan->getChannelMembers(); // add getter in Channel
    for (std::map<int, Client*>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (chan->isOperator(it->first))
            oss << "@" << it->second->getNick() << " ";
        else
            oss << it->second->getNick() << " ";
    }
    MessageSender::sendNumeric(_server.getServerName(), client, 353, oss.str());
    MessageSender::sendNumeric(_server.getServerName(), client, 366, chanName + " :End of /NAMES list");
}
