#include "CommandHandler.hpp"
#include "Server.hpp"

/*void CommandHandler::cmdPing(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    ParserResultPing *res = static_cast<ParserResultPing*>(result);

    //No need to be registered
    
    std::string pong = ":" + _server.getServerName() +
                       " PONG :" + token + "\r\n";

    MessageSender::sendToClient(client, pong);
}
*/