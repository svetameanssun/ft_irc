#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdPing(Client *client, AParserResult *result)
{
    (void) result;
    
    if (!client)
        return;

    std::string reply = "PING cmd not supported\r\n";
    log_warning(reply.c_str());
    MessageSender::sendToClient(client, reply);
}

//Not necessary for the project
/*void CommandHandler::cmdPong(Client *client, AParserResult *result)
{
    (void) result;

    if (!client) return;

    // You could log it or update a timestamp to track idle clients
    log_debug("[DEBUG] PONG received from %s (fd=%d)",
                client->getNick().c_str(), client->getFd());
}*/