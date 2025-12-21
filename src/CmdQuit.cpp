#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdQuit(Client *client, AParserResult *result)
{
    (void) client;
    (void) result;
    //if (!client || !result)
    //    return;
//
    //ParserResultQuit *res = static_cast<ParserResultQuit*>(result);
//
    //// RFC: message is optional
    //std::string quitMsg = res->getQuitMessage();
    //if (quitMsg.empty())
    //    quitMsg = "Client Quit";
//
    //// The prefix MUST be nick!user@host
    //std::string msg = ":" + client->getPrefix()
    //                  + " QUIT :" + quitMsg + "\r\n";
//
    //// 1) Notify all users sharing channels with this client
    //_server.getChannelManager().broadcastToJoinedChannels(client->getFd(), msg);
//
    //// 2) Remove from all channels
    //_server.getChannelManager().removeClientFromChannels(client);
//
    //// 3) Remove from server
    //_server.getClientManager().removeClient(client->getFd());
//
    ////TODO[NETWORKING](Networking layer must close the socket — not here)
}
