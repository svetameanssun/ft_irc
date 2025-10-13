#include "MessageSender.hpp"
#include <iostream>

// Send raw message
void MessageSender::sendToClient(Client *client, const std::string &msg)
{
    if (!client)
        return;

    // For now, write to std::cout instead of socket
    std::cout << "Sending to " << client->getNick() << ": " << msg;

    // TODO: Later: enable real network send message
    // TODO: Define which structure we use 
    // ::send(client->getFd(), msg.c_str(), msg.size(), 0);
}

// Send numeric reply
void MessageSender::sendNumeric(const std::string &serverName, Client *client,
                                int code, const std::string &msg)
{
    if (!client)
        return;

    std::ostringstream oss;
    oss << ":" << serverName << " " << code << " " << client->getNick()
        << " " << msg << "\r\n";

    sendToClient(client, oss.str());
}
