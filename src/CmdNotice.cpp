#include "CommandHandler.hpp"
#include "Server.hpp"

//TODO: It is a copy of "PrivMsg" but without responding to errors; if we modify PrivMsg, we need to modify this
void CommandHandler::cmdNotice(Client *client, AParserResult *result)
{
    if (!client || !result)
        return;

    // RFC 1459: NOTICE should not generate errors, BUT:
    // If not registered, silently ignore (NO ERR_NOTREGISTERED)
    if (!client->isRegistered())
        return;

    ParserResultNotice *result2 = static_cast<ParserResultNotice*>(result);
    std::vector<std::string> targetsVec = result2->getTargetVec();
    //TODO:Right now we just get the first target
    const std::string &target  = targetsVec.at(0);//params[0];
    //TODO: [LANA] Funny thing, when I receive the message, it is all joined, no spaces
    const std::string &message = result2->getNoticeMessage();//params[1];
    log_debug("Message: %s", message.c_str());

    // Channel NOTICE
    if (!target.empty() && target[0] == '#')
    {
        Channel *chan = _server.getChannelManager().findChannel(target);

        // If channel doesn't exist or user is not in it → silently ignore
        if (!chan || !chan->userExists(client->getFd()))
            return;

        std::string msg = ":" + client->getPrefix() +
                          " NOTICE " + target +
                          " :" + message + "\r\n";

        chan->broadcast(msg);
    }
    // Direct NOTICE to user
    else
    {
        Client *receiver = _server.getClientManager().findByNick(target);

        // No such nick → silently ignore
        if (!receiver)
            return;

        std::string msg = ":" + client->getPrefix() +
                          " NOTICE " + target +
                          " :" + message + "\r\n";

        MessageSender::sendToClient(receiver, msg);
    }
}
