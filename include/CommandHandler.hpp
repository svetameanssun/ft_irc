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
class AParserResult;


class CommandHandler
{
    private:
        Server &_server; // reference to server state

        // command implementations
        void cmdPass(Client *client, AParserResult *result);
        void cmdNick(Client *client, AParserResult *result);
        void cmdUser(Client *client, AParserResult *result);
        void cmdJoin(Client *client, AParserResult *result);
        void cmdPrivmsg(Client *client, AParserResult *result);
        void cmdNotice(Client *client, AParserResult *result);
        void cmdPart(Client *client, AParserResult *result);
        void cmdQuit(Client *client, AParserResult *result);
        void cmdPing(Client *client, AParserResult *result);
        void cmdPong(Client *client, AParserResult *result);
        void cmdMode(Client *client, AParserResult *result);
        void cmdTopic(Client *client, AParserResult *result);
        void cmdKick(Client *client, AParserResult *result);
        void cmdInvite(Client *client, AParserResult *result);
        bool flagNeedsParam(char c, bool adding);


        // Disallow copying
        CommandHandler(const CommandHandler &);
        CommandHandler &operator=(const CommandHandler &);

    public:
        CommandHandler(Server &server);
        ~CommandHandler() {}

        // entry point for commands
        void execute(Client *client, const std::string &command, AParserResult *result);
    };
