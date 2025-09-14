#pragma once

#include <string>
#include <sstream>
#include <unistd.h>   // for write()
#include <sys/socket.h>
#include "Client.hpp"

class MessageSender 
{
    public:
        // send raw message to client
        static void sendToClient(Client* client, const std::string& msg);

        // send numeric reply (RFC numerics)
        static void sendNumeric(const std::string& serverName, Client* client,
                            int code, const std::string& msg);
};
