#include "CommandHandler.hpp"
#include "Server.hpp"

/*void CommandHandler::cmdQuit(Client *client, AParserResult *result)
{
    if (!client || !result) return;

    std::string quitMsg = "Client Quit";
    if (!args.empty())
        quitMsg = args[0];

    // Build quit message
    std::string msg = ":" + client->getNick() + "!" + client->getUser() + "@" +
                      client->getHost() + " QUIT :" + quitMsg + "\r\n";

    // Broadcast QUIT to all channels
    _server.getChannelManager().broadcastToJoinedChannels(client->getFd(), msg);

    // Remove client from channels
    _server.getChannelManager().removeClientFromChannels(client);
    
    // Remove client from server
    _server.getClientManager().removeClient(client->getFd());
}
*/