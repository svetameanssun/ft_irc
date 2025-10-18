#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "MessageSender.hpp"
#include "utils.hpp"
#include "Client.hpp"


class Server;
class Client;


class CommandHandler
{
    private:
        Server &_server; // reference to server state

        // command implementations
        void cmdPass(Client *client, const std::vector<std::string> &args);
        void cmdJoin(Client *client, const std::vector<std::string> &args);
        void cmdNick(Client *client, const std::vector<std::string> &args);
        void cmdUser(Client *client, const std::vector<std::string> &args);
        void cmdPrivmsg(Client *client, const std::vector<std::string> &args);
        void cmdPart(Client *client, const std::vector<std::string> &args);
        void cmdQuit(Client *client, const std::vector<std::string> &args);
        void cmdPing(Client *client, const std::vector<std::string> &args);
        void cmdPong(Client *client, const std::vector<std::string> &args);
        void cmdMode(Client *client, const std::vector<std::string> &args);
        void cmdTopic(Client *client, const std::vector<std::string> &args);
        void cmdKick(Client *client, const std::vector<std::string> &args);
        void cmdInvite(Client *client, const std::vector<std::string> &args);

        // Disallow copying (orthodox canonical form, non-copyable)
        CommandHandler(const CommandHandler &);
        CommandHandler &operator=(const CommandHandler &);

    public:
        CommandHandler(Server &server);
        ~CommandHandler() {}

        // entry point for commands
        void execute(Client *client, const std::string &command,
                     const std::vector<std::string> &args);
};
