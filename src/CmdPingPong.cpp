#include "CommandHandler.hpp"
#include "Server.hpp"

/*void CommandHandler::cmdPing(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    ParcerResultPing *result2 = static_cast<ParcerResultPing*>(result);

    if (parsed->getParams().empty())
    {
        MessageSender::sendNumeric(_server.getServerName(), client, ERR_NOORIGIN, ":No origin specified");
        return;
    }

    const std::string &token = parsed->getParams()[0];
    std::string reply = "PONG :" + token + "\r\n";
    MessageSender::sendToClient(client, reply);
}
}*/

void CommandHandler::cmdPong(Client *client, AParserResult *result)
{
    (void) result;

    if (!client) return;

    // You could log it or update a timestamp to track idle clients
    log_debug("[DEBUG] PONG received from %s (fd=%d)",
                client->getNick().c_str(), client->getFd());
}
