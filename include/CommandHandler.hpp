#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "MessageSender.hpp"
#include "utils.hpp"
#include "Client.hpp"
#include "Replies.hpp"

class Server;
class Client;
class AParcerResult;


class CommandHandler
{
    private:
        Server &_server; // reference to server state

        // command implementations
        void cmdPass(Client *client, AParcerResult *result);
        void cmdNick(Client *client, AParcerResult *result);
        void cmdUser(Client *client, AParcerResult *result);
        void cmdJoin(Client *client, AParcerResult *result);
        void cmdPrivmsg(Client *client, AParcerResult *result);
        void cmdNotice(Client *client, AParcerResult *result);
        void cmdPart(Client *client, AParcerResult *result);
        //void cmdQuit(Client *client, AParcerResult *result);
        //void cmdPing(Client *client, AParcerResult *result);
        void cmdPong(Client *client, AParcerResult *result);
        //void cmdMode(Client *client, AParcerResult *result);
        void cmdTopic(Client *client, AParcerResult *result);
        void cmdKick(Client *client, AParcerResult *result);
        //void cmdInvite(Client *client, AParcerResult *result);


        // Disallow copying (orthodox canonical form, non-copyable)
        CommandHandler(const CommandHandler &);
        CommandHandler &operator=(const CommandHandler &);

    public:
        CommandHandler(Server &server);
        ~CommandHandler() {}

        // entry point for commands
        void execute(Client *client, const std::string &command, AParcerResult *result);
    };
