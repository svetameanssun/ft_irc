#pragma once

#include "Server.hpp"
#include "Client.hpp"

class ErrorReplies
{
    public:
        static void needMoreParams(Server &server, Client *client, const std::string &cmd);
        static void unknownCommand(Server &server, Client *client, const std::string &cmd);
        static void noSuchNick(Server &server, Client *client, const std::string &nick);
        static void noSuchChannel(Server &server, Client *client, const std::string &channel);
        static void notRegistered(Server &server, Client *client);
        static void alreadyRegistered(Server &server, Client *client);
        static void passwdMismatch(Server &server, Client *client);

        static void chooseError(Server &server, Client *client, int ret);
};
