#include "CommandHandler.hpp"
#include "Server.hpp"

void CommandHandler::cmdQuit(Client *client, AParserResult *result)
{
    (void) client;

    if (!client || !result)
        return;

    ParserResultQuit *res = static_cast<ParserResultQuit*>(result);

    // RFC: message is optional
    std::string quitMsg = res->getQuitMessage();
    if (quitMsg.empty())
        quitMsg = "Client Quit";

    _server.disconnectClient(client->getFd(), quitMsg);
}
