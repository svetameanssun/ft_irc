#include "MessageSender.hpp"
#include <iomanip>

// Send raw message
void MessageSender::sendToClient(Client *client, const std::string &msg)
{
    if (!client)
        return;

    ::send(client->getFd(), msg.c_str(), msg.size(), 0);
}

// Send numeric reply
void MessageSender::sendNumeric(const std::string &serverName, Client *client,
                                int code, const std::string &msg)
{
    if (!client)
        return;

    //Necessary to comply with the requirements of the 3 digit reply
    std::ostringstream oss;
    oss << ":" << serverName << " "
    << std::setw(3) << std::setfill('0') << code
    << " " << client->getNick()
    << " " << msg << "\r\n";

    sendToClient(client, oss.str());
}
